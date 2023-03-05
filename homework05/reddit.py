#!/usr/bin/env python3

import os
import sys
import requests
import json
import pprint

# Constants
ISGD_URL = 'http://is.gd/create.php'

# Functions

def usage(status=0):
    ''' Display usage information and exit with specified status '''
    print('''Usage: {} [options] URL_OR_SUBREDDIT

    -s          Shorten URLs using (default: False)
    -n LIMIT    Number of articles to display (default: 10)
    -o ORDERBY  Field to sort articles by (default: score)
    -t TITLELEN Truncate title to specified length (default: 60)
    '''.format(os.path.basename(sys.argv[0])))
    sys.exit(status)

def load_reddit_data(url):
    ''' Load reddit data from specified URL into dictionary

    >>> len(load_reddit_data('https://reddit.com/r/nba/.json')) >= 25
    True

    >>> load_reddit_data('linux')[0]['data']['subreddit']
    'linux'
    '''

    # IF statement used to test if it starts with http.  IF not its assumed its a subreddit
    if not url.startswith('http'):
        url = (f'https://reddit.com/r/{url}/.json')
    # used to get around reddit's defenses
    headers  = {'user-agent': 'reddit-{}'.format(os.environ.get('USER', 'cse-20289-sp22'))}
    response = requests.get(url, headers=headers)
    #convert
    webdata = response.text
    jsondata = json.loads(webdata)
    #return the reddit data as a list
    return jsondata['data']['children']
    

def shorten_url(url):
    ''' Shorten URL using is.gd service

    >>> shorten_url('https://reddit.com/r/aoe2')
    'https://is.gd/dL5bBZ'

    >>> shorten_url('https://cse.nd.edu')
    'https://is.gd/3gwUc8'
    '''
    # use is.gd service to generate shortened url.
    urlResponse = requests.get(ISGD_URL, params={'format': 'json', 'url': url})
    urlData = urlResponse.text
    urlJson = json.loads(urlData)
    url = urlJson['shorturl']
    return url

def print_reddit_data(data, limit=10, orderby='score', titlelen=60, shorten=False):
    ''' Dump reddit data based on specified attributes '''

    #if used to determine how data is sorted since it is different for certain keys
    if type(data[0]['data'][orderby]) == int:
        dataList = sorted(data, key=lambda p: p["data"][orderby], reverse=True)
    else:
        dataList = sorted(data, key=lambda p: p["data"][orderby])
    # for loops through data
    for index, data in enumerate(dataList[:limit],1):
        if index>1:
            print()


        title = data['data']['title'][:titlelen]
        score = data['data']['score']
        url = data['data']['url']


        if shorten:
            url = shorten_url(url)

        print(f'{index:4}.\t{title} (Score: {score})\n\t{url}')


def main():
    # default values
    arguments = sys.argv[1:]
    url       = None
    limit     = 10
    orderby   = 'score'
    titlelen  = 60
    shorten   = False

    #call usage if there aren't arguments input on command line
    if not arguments:
        usage(1)

    #pop() will act like a stack and give LIFO
    while arguments and arguments[0].startswith('-'):
        flag = arguments.pop(0)
        match flag:
            case '-h':
                usage(0)
            case '-s':
                shorten = True
            case '-n':
                limit = int(arguments.pop(0))
            case '-o':
                orderby = arguments.pop(0)
            case '-t':
                titlelen = int(arguments.pop(0))
            case _:
                usage(1)

    #Load data from url and then print the data      
    url = arguments.pop(0)
    postsList = load_reddit_data(url) 
    print_reddit_data(postsList, limit, orderby, titlelen, shorten)

# Main Execution

if __name__ == '__main__':
    main()
