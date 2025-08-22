import getopt
import sys
import os

def merge_binary_files(input_specs, output_file):
    """
    Merge binary files into a single output file at specified offsets
    :param input_specs: List of tuples [(filename, offset), ...]
    :param output_file: Output filename
    """
    # Validate files and calculate sizes
    file_sizes = {}
    for filename, offset in input_specs:
        if not os.path.exists(filename):
            raise FileNotFoundError(f"Input file not found: {filename}")
        file_size = os.path.getsize(filename)
        file_sizes[filename] = file_size

    # Check for address overlaps
    for i, (file1, offset1) in enumerate(input_specs):
        end1 = offset1 + file_sizes[file1]
        for j, (file2, offset2) in enumerate(input_specs):
            if i == j:
                continue
            end2 = offset2 + file_sizes[file2]
            if max(offset1, offset2) < min(end1, end2):
                raise ValueError(f"Address overlap detected: {file1} (0x{offset1:X}-0x{end1:X}) "
                                f"overlaps with {file2} (0x{offset2:X}-0x{end2:X})")

    # Determine total output size
    max_offset = max(offset + file_sizes[filename] for filename, offset in input_specs)

    # Write files at specified offsets
    with open(output_file, 'wb') as out_f:
        # Pre-allocate space
        out_f.truncate(max_offset)
        
        # Process files in address order
        for filename, offset in sorted(input_specs, key=lambda x: x[1]):
            file_size = file_sizes[filename]
            print(f"Writing {filename} at 0x{offset:X} ({file_size} bytes)...")
            
            with open(filename, 'rb') as in_f:
                out_f.seek(offset)
                bytes_written = 0
                while bytes_written < file_size:
                    chunk = in_f.read(4096)
                    if not chunk:
                        break
                    out_f.write(chunk)
                    bytes_written += len(chunk)
    
    print(f"Merge successful! Output: {output_file} (Total size: {max_offset} bytes)")

def main():
    short_opts = "i:a:o:h"
    long_opts = ["input=", "addr=", "output=", "help"]
    input_files = []
    addresses = []
    output_file = None

    try:
        opts, args = getopt.getopt(sys.argv[1:], short_opts, long_opts)
    except getopt.GetoptError as err:
        print(f"Argument error: {err}")
        print("Usage: merge.py -i <input> -a <address> [-i <input> -a <address>]... -o <output>")
        sys.exit(2)

    # Parse arguments
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            print("Binary File Merger")
            print("Usage: merge.py -i <input.bin> -a <hex_address> \\")
            print("                 [-i <input2.bin> -a <hex_address2>]... -o <output.bin>")
            print("Example: merge.py -i boot.bin -a 0x0 -i kernel.bin -a 0x1000 -o firmware.bin")
            sys.exit()
        elif opt in ('-i', '--input'):
            input_files.append(arg)
        elif opt in ('-a', '--addr'):
            try:
                # Convert hex/dec address to integer
                addresses.append(int(arg, 0))
            except ValueError:
                print(f"Invalid address format: {arg}")
                sys.exit(2)
        elif opt in ('-o', '--output'):
            output_file = arg

    # Validate arguments
    if not input_files or not addresses:
        print("Error: Must specify at least one input file with address")
        sys.exit(2)
    if len(input_files) != len(addresses):
        print(f"Error: {len(input_files)} input files but {len(addresses)} addresses specified")
        sys.exit(2)
    if not output_file:
        print("Error: Output file not specified")
        sys.exit(2)

    # Process files
    input_specs = list(zip(input_files, addresses))
    try:
        merge_binary_files(input_specs, output_file)
    except Exception as e:
        print(f"Merge failed: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
