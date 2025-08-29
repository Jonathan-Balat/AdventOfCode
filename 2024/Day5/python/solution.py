
def get_mid_value(ref_update) -> int:
    return ref_update[len(ref_update)//2]


def read_paragraph(ref_file, ref_list: list) -> list:
    raw_line = ref_file.readline().strip()
    while raw_line.__len__() > 0:
        ref_list.append(raw_line)
        raw_line = ref_file.readline().strip()

    return ref_list


def compile_rules(ref_list: list, ref_rules: dict) -> None:
    for item in ref_list:
        # Extract and cast numbers to integers
        base_num, valid_next_num = item.split("|")
        base_num = int(base_num)
        valid_next_num = int(valid_next_num)

        if ref_rules.get(base_num) is None:
            ref_rules[base_num] = [valid_next_num]
        else:
            ref_rules[base_num].append(valid_next_num)

    # Search for last number
    last_num = None
    for key, value in ref_rules.items():
        if len(value) == 1:
            last_num = value[0]
            break

    if last_num is not None:
        ref_rules[last_num] = []
    else:
        assert ValueError("No last number found!")


def format_page_updates(ref_updates: list) -> list:

    tmp_list = []
    for item in ref_updates:
        tmp_list.append([int(x) for x in item.split(',')])

    return tmp_list


def assess_page_update(ref_rules: dict, ref_update: list) -> bool:
    b_valid = True
    max_idx = len(ref_update)-1

    # Verify if update is correct
    for idx in range(0, max_idx):
        base_num = ref_update[idx]
        next_num = ref_update[idx+1]

        # print(base_num, next_num)
        if next_num not in ref_rules.get(base_num):
            b_valid = False
            break

    return b_valid


def fix_invalid_update(ref_rules: dict, ref_update: list) -> list:

    base_idx = 0
    next_idx = base_idx+1
    max_idx = len(ref_update)-1  # Set to zero-indexing

    while base_idx < max_idx:

        b_sorting = True
        while b_sorting:
            base_num = ref_update[base_idx]
            base_rule = ref_rules.get(base_num)

            # If number is in rule, check next number. Else, swap numbers
            if ref_update[next_idx] in base_rule:
                next_idx += 1
            else:
                ref_update[next_idx], ref_update[base_idx] = ref_update[base_idx], ref_update[next_idx]

            # Next index is out of bounds, end sorting
            if next_idx > max_idx:
                b_sorting = False

        # Move to next index to sort
        base_idx += 1
        next_idx = base_idx+1

    return ref_update


if __name__ == "__main__":

    page_rules_parse = []
    page_update_input = []
    page_rules = {}

    # Access file
    with open("../input.txt", "r") as file:

        # Reads page rules
        page_rules_parse = read_paragraph(file, page_rules_parse)
        # print('Total rules gathered =', len(page_rules_parse))

        # Reads page updates
        page_update_input = read_paragraph(file, page_update_input)
        # print('Total page updates gathered =', len(page_update_input))

        # Interpret page rules
        compile_rules(page_rules_parse, page_rules)
        # print(page_rules.items())

        # Format page updates
        page_update_input = format_page_updates(page_update_input)
        # print(page_update_input)

        total_sum = 0
        corrected_sum = 0
        for update in page_update_input:
            if assess_page_update(page_rules, update):
                total_sum += get_mid_value(update)
            else:
                # Correct update ordering
                fixed_update = fix_invalid_update(page_rules, update)
                corrected_sum += get_mid_value(fixed_update)

        print(f"Sum of correct updates {total_sum}.")
        print(f"Sum of corrected updates {corrected_sum}.")
