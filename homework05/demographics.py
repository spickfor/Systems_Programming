#!/usr/bin/env python3
import collections
import os
import sys
import csv
import requests
import pprint
import re

# Constants
URL     = 'https://yld.me/raw/e2Ad'
TAB     = ' '*8
GENDERS = ('M', 'F')
ETHNICS = ('B', 'C', 'N', 'O', 'S', 'T', 'U')

# Functions
def usage(status=0):
    ''' Display usage information and exit with specified status '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [options] [URL]

    -y  YEARS   Which years to display (default: all)
    -p          Display data as percentages.
    -G          Do not include gender information.
    -E          Do not include ethnic information.
    ''')
    sys.exit(status)

def load_demo_data(url=URL):
    ''' Load demographics from specified URL into dictionary

    >>> load_demo_data('https://yld.me/raw/ilG').keys()
    dict_keys(['2013', '2014', '2015', '2016', '2017', '2018', '2019'])

    >>> load_demo_data('https://yld.me/raw/ilG')['2013'] == {'M': 1, 'B': 2, 'F': 1, 'TOTAL': 2}
    True

    >>> load_demo_data('https://yld.me/raw/ilG')['2019'] == {'M': 1, 'U': 2, 'F': 1, 'TOTAL': 2}
    True
    '''

    #{'year': {'gender': count, 'ethnic': count, 'TOTAL': count}}
    
    csvResponse = requests.get(url)

    #create empty dictionary
    demographDict = collections.defaultdict(dict)
    for student in csv.reader(csvResponse.text.splitlines()):
        #skip if 'Year'
        if student[0] == 'Year':
            continue

        year, gender, ethnic = student
        #update dictionay
        demographDict[year][gender] = demographDict[year].get(gender, 0) + 1
        demographDict[year][ethnic] = demographDict[year].get(ethnic, 0) + 1
    #update totals
    for year in demographDict:
        demographDict[year]['TOTAL'] = demographDict[year]['M'] + demographDict[year]['F']


    return demographDict

def print_demo_separator(years, char='='):
    ''' Print demographics separator
    Note: The row consists of the 8 chars for each item in years + 1.

    >>> print_demo_separator(['2012', '2013'])
    ========================
    '''
    
    # TODO: Print row of separator characters
    print((char*8)*(len(years)+1))

def print_demo_years(years):
    ''' Print demographics years row

    Note: The row is prefixed by 4 spaces and each year is right aligned to 8
    spaces ({:>8}).

    >>> print_demo_years(['2012', '2013'])
            2012    2013
    '''
    # TODO: Print row of years
    print(f'    ', end='')
    for year in years:
        print(f'{year:>8}',end='')
    print()


def print_demo_fields(data, years, fields, percent=False):
    ''' Print demographics information (for particular fields)

    Note: The first column should be a 4-spaced field name ({:>4}), followed by
    8-spaced right aligned data columns ({:>8}).  If `percent` is True, then
    display a percentage ({:>7.1f}%) rather than the raw count.

    >>> data  = load_demo_data('https://yld.me/raw/ilG')
    >>> years = sorted(data.keys())
    >>> print_demo_fields(data, years, GENDERS, False)
       M       1       1       1       1       1       1       1
       F       1       1       1       1       1       1       1
    '''
    # For each field, print out a row consisting of data from each year.
    for field in fields:
        print(f'{field:>4}',end='')
        for year in years:
            num = (data[year]).get(field, 0)
            if percent:
                num = num/data[year]['TOTAL'] * 100
                print(f'{num:>7.1f}%',end='')
                #7.1 to account for % as extra trailing character
            else:
                print(f'{num:>8}',end='')
        #prints new blank line
        print()

def print_demo_data(data, years=None, percent=False, gender=True, ethnic=True):
    ''' Print demographics data for the specified years and attributes '''
    #if statement validates years, if None then take form data
    if not years:
        years = data.keys()
    years = sorted(years)
    
    print_demo_years(years)
    print_demo_separator(years)

    #ifs control what to print,years,gender,ethnicity
    if gender:
        print_demo_gender(data,years,percent)

    if ethnic:
        print_demo_ethnic(data, years, percent)

    

def print_demo_gender(data, years, percent=False):
    ''' Print demographics gender information '''
    print_demo_fields(data, years, GENDERS, percent)
    print_demo_separator(years, '-')

def print_demo_ethnic(data, years, percent=False):
    ''' Print demographics ethnic information '''
    print_demo_fields(data, years, ETHNICS, percent)
    print_demo_separator(years, '-')

def main():
    ''' Parse command line arguments, load data from url, and then print
    demographic data. '''

    # TODO: Parse command line arguments
    arguments = sys.argv[1:]
    url       = URL
    years     = None
    gender    = True
    ethnic    = True
    percent   = False

    while arguments and arguments[0].startswith('-'):
        flag = arguments.pop(0)
        match flag:
            case '-y':
                years = arguments.pop(0)
                years = years.split(',')
            case '-p':
                percent = True
            case '-E':
                ethnic = False
            case '-G':
                gender = False
            case '-h':
                usage(0)
            case _:
                usage(1)
    if arguments:
        url = arguments.pop(0)
    
       
    
    # TODO: Load data from url and then print demograpic data with specified
    # arguments
    
    #download csv file
    ''' csvResponse = requests.get(URL)
    for student in csv.reader(csvResponse.text.splitlines()):
        print(student)'''
    dictionary = load_demo_data(url)
    print_demo_data(dictionary, years, percent, gender, ethnic)


# Main Execution

if __name__ == '__main__':
    main()


