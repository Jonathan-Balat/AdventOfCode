
CHAR_MUL = "*"
CHAR_ADD = "+"
CHAR_CON = "||"
CHAR_ERROR = " "

CHAR_LIST = [CHAR_ADD, CHAR_MUL]

operation_list = []

def generate_suboperation(refResult: int, operation_str: str, values: list) -> str:

    # Iterates over n-1 possible combinations of operators
    for operator in CHAR_LIST:
        sub_operation_str = f"({operation_str}{operator}{values[0]})"

        if (len(values)-1 > 0):
            generate_suboperation(refResult, sub_operation_str, values[1:])
        else:
            operation_list.append((refResult, sub_operation_str))


def generate_equations(data_dict) -> None:
    
    for refResult, values in data_dict.items():
        generate_suboperation(refResult, values[0], values[1:])
    
def compute_operations(operation_list: list) -> int:
    sum = 0
    lastRefResult = 0
    for refResult, operation in operation_list:
        result = eval(operation)
        # print(f"Result: {refResult}, Operation:{(operation)} = {result}")

        if int(refResult) == result:
            if lastRefResult != refResult:
                sum += result
                lastRefResult = refResult

    return sum

if __name__ == "__main__":

    # Access file
    with open("../input.txt", "r") as file:
        data_dict = {}

        # Update data_dict with file contents
        for item in file:
            # Remove newline character
            item = item.strip()
            # print(f"Processing: {item}")
            
            result, values = item.split(":")
            # print(f"Result: {result}, Values: {values.split(' ')[1:]}")

            data_dict[result] = values.split(' ')[1:]
        
    generate_equations(data_dict.copy())

    total = compute_operations(operation_list)
    
    print(f"Total: {total}")

    # # DEBUG
    # for operation in operation_dict.values():
    #     print(f"Operation: {operation}")
        
