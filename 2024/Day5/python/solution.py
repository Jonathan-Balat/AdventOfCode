
page_rules_parse = []
page_update_input = []

page_rules = {}


def read_paragraph(ref_file, ref_list: list) -> list:
    raw_line = ref_file.readline().strip()
    while raw_line.__len__() > 0:
        ref_list.append(raw_line)
        raw_line = ref_file.readline().strip()

    return ref_list

def compile_rules(ref_list: list, ref_rules:dict) -> None:
    for item in ref_list:
        base_num, valid_next_num = item.split("|")

        base_num = int(base_num)
        valid_next_num = int(valid_next_num)

        if ref_rules.get(base_num) is None:
            ref_rules[int(base_num)] = [int(valid_next_num)]
        else:
            ref_rules[int(base_num)].append(int(valid_next_num))

    last_num = None
    # Search for last number
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

def assess_page_update(ref_rules, ref_update) -> int:
    ret_val = 0
    b_valid = True

    max_idx = len(ref_update)-1
    mid_idx = len(ref_update)//2

    # Verify if update is correct
    for idx in range(0, max_idx):
        base_num = ref_update[idx]
        next_num = ref_update[idx+1]

        # print(base_num, next_num)
        if next_num not in ref_rules.get(base_num):
            b_valid = False
            break

    # Return mid number
    if b_valid:
        ret_val = ref_update[mid_idx]

    return ret_val

if __name__ == "__main__":

    CHR_SPACE = " "
    CHR_NEXT_LINE = "\n"

    # Access file
    with open("../input.txt", "r") as file:

        # Reads page rules
        page_rules_parse = read_paragraph(file, page_rules_parse)
        print('Total rules gathered =', len(page_rules_parse))

        # Reads page updates
        page_update_input = read_paragraph(file, page_update_input)
        print('Total page updates gathered =', len(page_update_input))

        # Interpret page rules
        compile_rules(page_rules_parse, page_rules)
        # print(page_rules.items())

        # Format page updates
        page_update_input = format_page_updates(page_update_input)
        # print(page_update_input)

        sum = 0
        for update in page_update_input:
            sum += assess_page_update(page_rules, update)

        print(sum)