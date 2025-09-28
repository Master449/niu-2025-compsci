# David Flowers II
# Z1942130
# Assignment 5
# Koop FA2024

import re
from sys import argv
from .util import get_data

def get_by_brand(br):
    '''Searches the data by the brands owner company.

    Args:
       String: The company to search for.

    Returns:
       List of items that match the searched brand.
    '''
    data = get_data()
    results = []

    for item in data:
        if item['brand_owner'].upper() == br.upper():
            results.append(item)

    return results

def get_by_description(de):
    '''Searches for arg through the description field.

    Args:
       String (Regex): Words to search for

    Returns:
       List: Search results matching the search term
    '''
    data = get_data()
    results = []
    search = de.upper().replace('*', '.*')

    for item in data:
        if re.search(search, item['description'].upper()):
            results.append(item)

    return results

def filter_by_category(ce, items):
    '''Searches for arg through the description field.

    Args:
       String (Regex): Words to search for

    Returns:
       List: Search results matching the search term
    '''
    results = []

    for item in items:
        if item['branded_food_category'].upper() == ce.upper():
            results.append(item)

    return results

if __name__ == "__main__":
    if len(argv) == 5:
        if argv[1] == "-b" or argv[3] == "-b":
            if argv[1] == "-c":
                temp = get_by_brand(argv[4])
                output = filter_by_category(argv[2], temp)
            else:
                temp = get_by_brand(argv[2])
                output = filter_by_category(argv[4], temp)

        elif argv[1] == "-d" or argv[3] == "-d":
            if argv[1] == "-c":
                temp = get_by_description(argv[4])
                output = filter_by_category(argv[2], temp)
            else:
                temp = get_by_description(argv[2])
                output = filter_by_category(argv[4], temp)
        else:
            print("Usage: python -m food_data.find -b <brand> | -d <description>")

        for item in output:
            print(f"{item["fdc_id"]} {item["brand_owner"]} {item["description"]}")

    elif len(argv) == 3 and (argv[1] == "-b" or argv[1] == "-d"):
        if argv[1] == "-b":
            output = get_by_brand(argv[2])
        elif argv[1] == "-d":
            output = get_by_description(argv[2])

        for item in output:
            print(f"{item["fdc_id"]} {item["brand_owner"]} {item["description"]}")

    else:
        print("Usage: python -m food_data.find -b <brand> | -d <description>")

# If that spaghetti terrifies you, my original solution was the one below using argparser module.
# but I assumed he wanted us to implement the details ourselves.

# if __name__ == "__main__":
#     if len(argv) == 3 or len(argv) == 5:
#         parser = argparse.ArgumentParser()
#         group = parser.add_mutually_exclusive_group(required=True)

#         group.add_argument("-b")
#         group.add_argument("-d")
#         parser.add_argument("-c")

#         args = parser.parse_args()

#         if args.b:
#             if args.c:
#                 temp = get_by_brand(args.b)
#                 output = filter_by_category(args.c, temp)
#             else:
#                 output = get_by_brand(args.b)
        
#         if args.d:
#             if args.c:
#                 temp = get_by_description(args.d)
#                 output = filter_by_category(args.c, temp)
#             else:
#                 output = get_by_brand(args.b)

        
#         for item in output:
#             print(f"{item["fdc_id"]} {item["brand_owner"]} {item["description"]}")

#     else:
#         print("Usage: python -m food_data.find -b <brand> | -d <description>")
