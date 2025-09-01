from dataclasses import dataclass


@dataclass
class Antenna:

    id_instance_dict = {}

    id: int = None
    frequency: str = ""
    x: int = 0
    y: int = 0

    def __init__(self, frequency: str, x: int, y: int):
        if frequency in Antenna.id_instance_dict.keys():
            Antenna.id_instance_dict[frequency] += 1
        else:
            Antenna.id_instance_dict[frequency] = 1

        self.id = Antenna.id_instance_dict[frequency]
        self.frequency = frequency
        self.x = x
        self.y = y


def extract_unique_frequencies(ant_dict, frequency_list, scan_line, y_idx):
    # Remove newline character
    for character in scan_line:
        if character in ["\n", " ", "."]:
            continue

        if character not in frequency_list:
            frequency_list.append(character)

        x_idx = scan_line.index(character)
        if character not in ant_dict.keys():
            ant_dict[character] = [Antenna( frequency=character, x=x_idx, y=y_idx)]
        else:
            ant_dict[character].append(Antenna(frequency=character, x=x_idx, y=y_idx))

    return ant_dict, frequency_list


def compute(A, B):
    diff_x = abs(A[0] - B[0])
    diff_y = abs(A[1] - B[1])
    return diff_x, diff_y


def get_map_and_boundary(file):
    # Define area boundary
    map_copy_list = file.readlines()

    y_bound = len(map_copy_list)
    x_bound = len(map_copy_list[0])

    map_boundary = (x_bound, y_bound)

    return map_copy_list, map_boundary


def generate_anodes(ant_dict: dict):
    anode_loc_list = []
    for freq, antenna_list in ant_dict.items():
        node_comb_list = []

        for antenna_ref in antenna_list:
            for antenna_comp in antenna_list:

                # If comparing same antenna, skip
                if antenna_ref == antenna_comp:
                    # print("Skipped")
                    continue

                combination = (antenna_ref, antenna_comp) if antenna_ref.id < antenna_comp.id \
                                                          else (antenna_comp, antenna_ref)
                if combination in node_comb_list:
                    continue

                node_comb_list.append(combination)
                # print(f"Comparing {antenna_ref} with {antenna_comp}")
                diff_x, diff_y = compute(
                    (antenna_ref.x, antenna_ref.y),
                    (antenna_comp.x, antenna_comp.y)
                )

                # NOTE: don't forget y-axis is inverted as origin starts from top-left
                Anode_A_pos = (antenna_ref.x + diff_x, antenna_ref.y + diff_y)
                Anode_B_pos = (antenna_comp.x - diff_x, antenna_comp.y - diff_y)
                # print(f"Anode A position {Anode_A_pos}")
                # print(f"Anode B position {Anode_B_pos}")

                if 0 < Anode_A_pos[0] <= area_boundary[0] and 0 < Anode_A_pos[1] <= area_boundary[1]:
                    if Anode_A_pos not in anode_loc_list:
                        anode_loc_list.append(Anode_A_pos)

                if 0 < Anode_B_pos[0] <= area_boundary[0] and 0 < Anode_B_pos[1] <= area_boundary[1]:
                    if Anode_B_pos not in anode_loc_list:
                        anode_loc_list.append(Anode_B_pos)

    return anode_loc_list


if __name__ == "__main__":

    freq_list = []
    antenna_dict = {}

    # Access file
    with open("../input.txt", "r") as file:
        local_map_copy_list, area_boundary = get_map_and_boundary(file)

    # Extract different "frequencies" and antennas
    for y_idx, item in enumerate(local_map_copy_list):
        antenna_dict, freq_list = extract_unique_frequencies(antenna_dict, freq_list, item, y_idx)

    # Generate Anodes per frequency
    anti_node_loc_list = generate_anodes(antenna_dict)

    print(f"ANODES", anti_node_loc_list, anti_node_loc_list.__len__())
