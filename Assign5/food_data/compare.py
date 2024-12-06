# David Flowers II
# Z1942130
# Assignment 5
# Koop FA2024
from .util import parse_ingredients
from .util import get_data
from sys import argv

# Private helper method for searching
def __find_id(id_one, id_two, field):
    data = get_data()
    item_one = None
    item_two = None
    ss_one = 0
    ss_two = ""
    
    for item in data:
        # Find matching id for id_one
        if item["fdc_id"] == id_one:
            item_one = item[field]
            ss_one = [item["serving_size"], item["serving_size_unit"]]
        # Find matching id for id_two
        if item["fdc_id"] == id_two:
            item_two = item[field]
            ss_two = [item["serving_size"], item["serving_size_unit"]]
        # If we found both, no need to continue the loop
        if item_one and item_two:
            break

    return item_one, item_two, ss_one, ss_two


def diff_nutrition(id_one, id_two):
    '''Compares nutrition information of two passed in food IDs.

    Args:
       Int: id_one - fdc_id of food item one.
       Int: id_two - fdc_id of food item two.

    Returns:
       List of Tuples: Difference in nutrition data
    '''
    differences = []
    # Retreived from helper function
    nut_one, nut_two, ss_one, ss_two = __find_id(id_one, id_two, "nutrition")

    # Iterate through both lists
    # Shouldn't be too bad as long as nutrition facts aren't 2^512 items long
    for item_one in nut_one:
        for item_two in nut_two:
            if item_one['name'] == item_two['name']:

                # Convert MG -> G or G -> MG for differences
                if item_two['unit_name'] == 'G' and item_one['unit_name'] == 'MG':
                    amount_one = item_one['amount'] / 1000
                elif item_two['unit_name'] == 'MG' and item_one['unit_name'] == 'G':
                    amount_one = item_one['amount'] * 1000
                else:
                    amount_one = item_one['amount']

                # Calculate difference
                difference = item_two["amount"] - amount_one

                # Append them to the list
                differences.append((item_one['name'], difference, item_two['unit_name']))
                
                # If match was found, no need to continue
                break

    serving_diff = ss_one[0] - ss_two[0]
    differences.append(('Serving Size', serving_diff, ss_one[1]))

    return differences

def diff_ingredients(id_one, id_two):
    '''Compares ingredient information of two passed in food IDs.

    Args:
       Int: id_one - fdc_id of food item one.
       Int: id_two - fdc_id of food item two.

    Returns:
       List of sets: Shared ingredient set, and each respective set 
    '''
    all_ingred = set()
    shared_items = set()
    respective_one = set()
    respective_two = set()

    # Serving sizes are ignored in this function
    item_one, item_two, ss1, ss2 = __find_id(id_one, id_two, "ingredients")

    # Parse ingredients and convert to sets
    item_one = set(parse_ingredients(item_one))
    item_two = set(parse_ingredients(item_two))

    shared_items = item_one & item_two
    respective_one = item_one - item_two
    respective_two = item_two - item_one

    # one and two are flipped to match output
    return (shared_items, respective_two, respective_one)

if __name__ == "__main__":
    output = ""

    # IDs are integers, arguments are strings
    id_one = int(argv[2])
    id_two = int(argv[3])

    if len(argv) == 4:
        if argv[1] == "-n":
            output = diff_nutrition(id_one, id_two)

            for item in output:
                temp = list(item)
                print(f"{temp[0]}: {"{:.1f}".format(temp[1])} {temp[2]}")
                
        elif argv[1] == "-i":
            shared, two, one = diff_ingredients(id_one, id_two)

            for item in shared:
                print(f"  {item}")
            for item in one:
                print(f"- {item}")
            for item in two:
                print(f"+ {item}")

    else:
        print("Usage: python -m food_data.find -b <brand> | -d <description>")