
# ENUMS
CHAR_WALL = '#'
CHAR_WALKED = 'X'
CHAR_UP = '^'
CHAR_RIGHT = '>'
CHAR_DOWN = 'v'
CHAR_LEFT = '<'
DIR_UP = 0
DIR_RIGHT = 1
DIR_DOWN = 2
DIR_LEFT = 3

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
        row = map_arr[tr_y + dy][:]

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
        new_char = CHAR_WALKED
        try:
            # Determine if will step forward or turn
            if map_arr[tr_y + dy][tr_x + dx] == CHAR_WALL:
                new_char, tr_dir = turn_direction(tr_dir)
                b_collision = True
                
        except IndexError:
            # Excited from map
            b_exited = True

        # Update character
        map_arr[tr_y + y] = row[:(tr_x + x)] + new_char + row[(tr_x + x + 1):]
        
    # Commit steps to current position
    curr_pos = (tr_x + x, tr_y + y, tr_dir)

    return curr_pos, b_exited

def turn_direction(direction: int) -> tuple:

    # Increment but reset to zero, when out of bounds
    direction += 1
    if direction > DIR_LEFT:
        direction = 0

    if direction == DIR_UP:
        character = CHAR_UP
    elif direction == DIR_RIGHT:
        character = CHAR_RIGHT
    elif direction == DIR_DOWN:
        character = CHAR_DOWN
    else:
        character = CHAR_LEFT

    return character, direction


if __name__ == "__main__":

    # Access file
    with open("../input.txt", "r") as file:

        map_array = generate_map(file)

        # Loops over each row of map to find the starting position (Assumed as facing up - CHAR_UP)
        for y_pos,item in enumerate(map_array):
            x_pos =  item.find(CHAR_UP)
            if x_pos > -1:
                curr_position = (x_pos, y_pos, DIR_UP)

        b_done = False
        while not b_done:
            curr_position, b_done = project_line(map_array, curr_position)

        # Finalize count of walked spots
        sum_walked = 0
        for item in map_array:
            sum_walked += item.count(CHAR_WALKED)

        print("Total walked spots =", sum_walked)
