__current_value = 50
__zeroed_count = 0

def increment_zeroed_count():
    global __zeroed_count
    __zeroed_count+=1

def rotate_value(current_value, instruction):

    if "L" in instruction:
        instruction = instruction.strip("L")
        direction = -1
    elif "R" in instruction:
        instruction = instruction.strip("R")
        direction = 1
    else:
        raise ValueError("Invalid instruction")

    steps = int(instruction)

    while steps > 100:
        increment_zeroed_count()
        steps -= 100

    if ((((current_value-steps < 0) and (direction == -1) or
        (current_value+steps > 100) and (direction == 1))) and
            (current_value != 0)):
        print(f"Instruction: {instruction}, Direction: {'Left' if direction==-1 else 'Right'}, Steps: {steps}, Current Value: {current_value} - COUNT!")
        increment_zeroed_count()

    new_value = (current_value + direction*steps)%100

    if new_value == 0:
        increment_zeroed_count()

    print(f"Instruction: {instruction}, Direction: {'Left' if direction==-1 else 'Right'}, Steps: {steps}, New Value: {new_value}")

    return new_value


if __name__ == "__main__":
    with open("input.txt", "r") as f:
        lines = f.readlines()

        for line in lines:
            __current_value = rotate_value(__current_value, line.strip())

    print(f"Final Value: {__current_value}, Zeroed Count: {__zeroed_count}")