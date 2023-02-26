#!/usr/bin/env python3
#rpn.py
#Author: Seth Pickford

import os
import sys
import math

# Globals

OPERATORS = {'+', '-', '*', '/'}

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname}

By default, {progname} will process expressions from standard input.''')

    sys.exit(status)

#display error
def error(message):
    ''' Display error message and exit with error. '''
    print(message, file=sys.stderr)
    sys.exit(1)

# carries out the actual operations
def evaluate_operation(operation, operand1, operand2):
    ''' Return the result of evaluating the operation with operand1 and
    operand2.

    >>> evaluate_operation('+', 4, 2)
    6

    >>> evaluate_operation('-', 4, 2)
    2

    >>> evaluate_operation('*', 4, 2)
    8

    >>> evaluate_operation('/', 4, 2)
    2.0
    '''

    if operation == '+':
        answer = operand1 + operand2
    elif operation == '-':
        answer = operand1 - operand2
    elif operation == '*':
        answer = operand1 * operand2
    elif operation == '/':
        if operand2 == 0:
            print("Cannot divide by zero")
        else:
            answer = operand1 / operand2
    return answer

# calls function that does operations and evaluates errors
def evaluate_expression(expression):
    ''' Return the result of evaluating the RPN expression.

    >>> evaluate_expression('4 2 +')
    6.0

    >>> evaluate_expression('4 2 -')
    2.0

    >>> evaluate_expression('4 2 *')
    8.0

    >>> evaluate_expression('4 2 /')
    2.0

    >>> evaluate_expression('4 +')
    Traceback (most recent call last):
    ...
    SystemExit: 1

    >>> evaluate_expression('a b +')
    Traceback (most recent call last):
    ...
    SystemExit: 1
    '''
    stack = []
    for word in expression.split():
        if word in OPERATORS:
            if len(stack) < 2:
                error("Not enough arguments")
            else:
                element1 = stack.pop()
                element2 = stack.pop()
                result = evaluate_operation(word,element2,element1)
                stack.append(result)
        else:
            try: 
                result = float(word)
                stack.append(result)
            except ValueError:
                error("Not a number")

    if len(stack) != 1:
        error("Error: Too many operands")

    return stack.pop()

        

def main():
    ''' Parse command line arguments and process expressions from standard
    input. '''    
    arguments = sys.argv[1:]
    if len(arguments) > 0:
        usage(1)
    
    for line in sys.stdin: 
        line = line.rstrip()
        output = evaluate_expression(line)
        print(output)

# Main Execution

if __name__ == '__main__':
    main()