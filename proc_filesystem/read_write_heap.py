#!/usr/bin/python3
"""
This file looks for a process by it's pid
and replace a value in the heap of this process
"""

from sys import argv

def main():
    """
    This is the main function
    """
    if len(argv) < 4:
        print("Not enough args :(")
        exit(1)
    pid = argv[1]
    target_string = argv[2]
    replace_string = argv[3]
    
    # try to open the files
    try:
        maps_file = open("/proc/{}/maps".format(pid), 'r')
        mem_file = open("/proc/{}/mem".format(pid), 'r+b', 0)
    except Exception as e:
        print(e)
        maps_file.close()
        mem_file.close()
        exit(1)
    for line in maps_file.readlines():
        line_splitted = line.split()
        # once the heap line is found, get the adresses
        if '[heap]' in line_splitted:
            mem_positions = line_splitted[0].split('-')
            start_position = int(mem_positions[0], 16)
            end_position = int(mem_positions[1], 16)
            # move to the start position and read the values
            mem_file.seek(start_position)
            string_read = mem_file.read(end_position - start_position)
            # find the position of the target_string
            lookup_position = string_read.find(str.encode(target_string))
            # if there's no target_string found, break the loop
            if lookup_position < 0:
                break
            else:
                # move to the target_string and write the new value
                mem_file.seek(start_position + lookup_position)
                mem_file.write(str.encode(replace_string) + b'\x00')
            break
    # never forget to close openned files at the end
    maps_file.close()
    mem_file.close()

if __name__ == "__main__":
    main()
