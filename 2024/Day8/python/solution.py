from dataclasses import dataclass


@dataclass
class Antenna:
    id: int = None
    frequency: str = ""
    x: int = 0
    y: int = 0

freq_list = []
antenna_dict = {}
anti_node_loc_list = []
area_boundary = ()


def extract_unique_frequencies(scan_line, y_idx):
    # Remove newline character
    for character in scan_line:
        if character not in ["\n", " ", "."]:
            if character not in freq_list:
                freq_list.append(character)

            x_idx = scan_line.index(character)

            if character not in antenna_dict.keys():
                antenna_dict[character] = [
                    Antenna(
                        id=0,
                        frequency=character,
                        x=x_idx,
                        y=y_idx
                    )
                ]
            else:
                antenna_dict[character].append(
                    Antenna(
                        id=0,
                        frequency=character,
                        x=x_idx,
                        y=y_idx
                    )
                )


def n_combination(n):
    return n*(n-1)


def compute(A, B):
    diff_x = abs(A[0] - B[0])
    diff_y = abs(A[1] - B[1])
    return diff_x, diff_y


if __name__ == "__main__":

    # Access file
    with open("../input.txt", "r") as file:
        data_dict = {}

        # Define area boundary
        y_bound = len(file.readlines())
        x_bound = len(file.readlines()[0])
        area_boundary = (x_bound, y_bound)

        # Extract different "frequencies" and antennas
        for y_idx, item in enumerate(file):
            extract_unique_frequencies(item, y_idx)

    # Extract antennas present
    # for freq, antenna in antenna_dict.items():
    #     print(f"ENTRIES{freq}, {antenna}")

    for freq, antenna_list in antenna_dict.items():
        anti_node_loc_list = []

        for antenna_ref in antenna_list:
            for antenna_comp in antenna_list:
                print(f"Comparing {antenna_ref} with {antenna_comp}", end="")
                # If comparing same antenna, skip
                if antenna_ref == antenna_comp:
                    print("")
                    break
                print("Added")
                diff_x, diff_y = compute(
                    (antenna_ref.x, antenna_ref.y),
                    (antenna_comp.x, antenna_comp.y)
                )

                pos_diff_x = (antenna_ref.x - antenna_comp.x)
                pos_diff_y = (antenna_ref.y - antenna_comp.y)

                # Get ANode #1
                if pos_diff_x>0 and pos_diff_y>0:
                    ...
                elif pos_diff_x>0 and pos_diff_y<0:
                    ...
                elif pos_diff_x<0 and pos_diff_y>0:
                    ...
                elif pos_diff_x<0 and pos_diff_y<0:
                    ...
                else:
                   ...
                node_x = antenna_ref.x + diff_x

                # Get ANode #2


                anti_node_loc_list.append((diff_x, diff_y))
    print(anti_node_loc_list)
