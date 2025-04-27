
def generate_map(ref_file) -> list:
    map_arr = []
    raw_line = ref_file.readline().strip()
    while raw_line.__len__() > 0:
        map_arr.append(raw_line)
        raw_line = ref_file.readline().strip()

    return map_arr


def project_line(map_arr:list, curr_pos: tuple) -> tuple:
    tr_x, tr_y, tr_dir = curr_pos

    dx, dy = 0, 0  # next move
    x, y = 0, 0    # committed move
    b_exited = False
    b_collision = False
    while not b_collision and not b_exited:
        x, y = dx, dy

        # Get copy of current row before changes
        row = map_arr[tr_y + dy]

        # Sets sign based on tr_dir
        if tr_dir == DIR_UP:
            dy -= 1
        elif tr_dir == DIR_RIGHT:
            dx += 1
        elif tr_dir == DIR_DOWN:
            dy += 1
        else:  # DIR_LEFT
            dx -= 1

        # Verifies if found Wall, set new character
        try:
            if map_arr[tr_y + dy][tr_x + dx] == CHAR_WALL:
                b_collision = True

                # Update character
                dir_char, tr_dir = turn_direction(tr_dir)
                map_arr[tr_y + y] = row[:(tr_x + x)] + dir_char + row[(tr_x + x + 1):]
            else:  # Else set walked character
                map_arr[tr_y + y] = row[:(tr_x + x)] + CHAR_WALKED + row[(tr_x + x + 1):]
        except IndexError:
            b_exited = True
            map_arr[tr_y + y] = row[:(tr_x + x)] + CHAR_WALKED + row[(tr_x + x + 1):]

    # Commit steps to current position
    curr_pos = (tr_x + x, tr_y + y, tr_dir)

    return curr_pos, b_exited

def turn_direction(direction: int) -> tuple:

    direction += 1
    if direction > DIR_LEFT:
        direction = 0

    if direction == DIR_UP:
        character = '^'
    elif direction == DIR_RIGHT:
        character = '>'
    elif direction == DIR_DOWN:
        character = 'v'
    else:  # DIR_LEFT
        character = '<'

    return character, direction

if __name__ == "__main__":

    CHAR_WALL = '#'
    CHAR_WALKED = 'X'
    DIR_UP = 0
    DIR_RIGHT = 1
    DIR_DOWN = 2
    DIR_LEFT = 3

    # Access file
    with open("../input.txt", "r") as file:

        map_array = generate_map(file)

        # First time, get position when found
        for y_pos,item in enumerate(map_array):
            x_pos =  item.find("^")
            if x_pos > -1:
                curr_position = (x_pos, y_pos, DIR_UP)

        b_done = False
        while not b_done:
            curr_position, b_done = project_line(map_array, curr_position)

        sum_walked = 0
        for item in map_array:
            sum_walked += item.count(CHAR_WALKED)
            # print(item)
        print("Total walked spots =", sum_walked)
