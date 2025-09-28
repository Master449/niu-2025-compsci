# David Flowers II
# Z1942130
# Assignment 5
# Koop FA2024

import os
import json

from pathlib import Path
from urllib.request import urlretrieve

dataset = None
local_data_path = Path(__file__).parent / os.path.basename("https://faculty.cs.niu.edu/~dakoop/cs503-2024fa/a3/food-data-sample.json")

# 1a. Data Utilities (15 pts)
def download_data():
    '''Downloads the JSON data file from a url argument.
    The function only downloads the file if it does not exist.

    Args:
        string: URL of the data to download
    '''
    global local_data_path
    if not os.path.exists(local_data_path):
        urlretrieve(url, local_data_path)

def get_data():
    '''Processes the data retreived from download_data
    The function only processes the data, if the global
    variable doesn't contain data yet.

    Returns:
       JSON: The downloaded JSON object
    '''
    global dataset
    global local_data_path

    if dataset is None:
        dataset = json.load(open(local_data_path))

    return dataset

# Directions were unclear if this is meant to do it to all the items
# preemptively. Specifically 1a making no reference to an argument,
# and then 1c making refence to individual ingredient lists.
# Both are implemented below.
def parse_ingredients(ingred=None, all=None):
    '''Converts 'ingredients' key from string to list of strings.
    Boolean ALL flag takes precedence over ingredient.

    Args:
        String: Ingredients to be converted to list of strings
        Bool: Flag for converting all of the data (ignoring ingred arg)

    Returns: 
        List: The split string by ','
    '''
    if all:
        global dataset
        temp = dataset
        new_list = list()
    
        for item in temp:
            if item["ingredients"]:
                item['ingredients'] = [x.strip() for x in item["ingredients"].split(',')]

        dataset = temp
        return dataset
    elif ingred:
        return [x.strip() for x in ingred.split(',')]
    else:
        raise Exception("No arguement was supplied, function should be used with either ingred or all flag should be used.")

