def str_check_repetition(value):
    # Convert to string, split into 2.
    str_start = str(value)
    str_start_len = len(str_start)

    str_up_nib = str_start[:str_start_len // 2]
    str_down_nib = str_start[str_start_len // 2:]

    return str_up_nib == str_down_nib

def bin_check_repetition(value):
    # Convert to binary, remove prefix
    bin_start = bin(int(value))[2:]

    # Get length to split into 2.
    bin_start_len = len(bin_start)

    bin_up_nib = bin_start[:bin_start_len // 2]
    bin_down_nib = bin_start[bin_start_len // 2:]

    print(bin_start, "--->", bin_up_nib, bin_down_nib)

if __name__ == "__main__":
    with open("sample.txt", "r") as f:
        lines = f.readline()
        ranges = lines.split(",")

        sum = 0
        for range_val in ranges:
            val_start, val_end = range_val.split("-")
            for val in range(int(val_start), int(val_end) + 1):
                isRepeat = str_check_repetition(val)
                # print(val, "-->", isRepeat)
                if isRepeat:
                    sum += val
        print(sum)
