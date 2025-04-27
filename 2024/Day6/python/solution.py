
def generate_map(ref_file) -> list:
    map_arr = []
    raw_line = ref_file.readline().strip()
    while raw_line.__len__() > 0:
        map_arr.append(raw_line)
        raw_line = ref_file.readline().strip()

    return map_arr

def project_line(map_arr:list) -> list:
    ...
    return []

def turn_direction(map_arr: list) -> list:
    ...
    return []

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

        for item in map_array:
            print(item)

        # First time, get position
        for y_pos,item in enumerate(map_array):
            x_pos =  item.find("^")
            if x_pos > -1:
                curr_position = (x_pos, y_pos, DIR_UP)

        print(curr_position)
        tr_x, tr_y, dir = curr_position

        # Determine direction
        dx, dy = 0, 0

        b_collision = False
        while not b_collision:
            x, y = dx, dy

            map_array[tr_y + dy] = map_array[tr_y + dy][:(tr_x + dx)] + CHAR_WALKED + map_array[tr_y + dy][(tr_x + dx+1):]

            # Sets sign based on direction
            if dir == DIR_UP:
                dy -= 1
            elif dir == DIR_RIGHT:
                dx += 1
            elif dir == DIR_DOWN:
                dx -= 1
            else:  # DIR_LEFT
                dy += 1

            # print(dx, dy)

            # Verifies if found Wall
            if map_array[tr_y+dy][tr_x+dx] == CHAR_WALL:
                map_array[tr_y + dy] = map_array[tr_y + dy][:(tr_x + dx)] + CHAR_WALL + map_array[tr_y + dy][
                                                                                          (tr_x + dx + 1):]
                b_collision = True



        # Commit steps to current position
        tr_y += y
        tr_x += x

        print(tr_x, tr_y)

        for item in map_array:
            print(item)
