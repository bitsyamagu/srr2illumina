#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define MAX_LINE_LENGTH 1001  // 1000 characters + NULL terminator
#define DEFAULT_INDEX "TCTTAACTGG+TTCAGGCCGA"  // Default index sequence

// Convert SRA format to Illumina format
char* convert_to_illumina_format(const char* sra_header, int read_number) {
    static char illumina_header[MAX_LINE_LENGTH];
    
    // SRA format: @SRR33684863.1 HWI-ST808:130:H0B8YADXX:1:1101:1914:2223 length=101
    // Illumina format: @HWI-ST808:130:H0B8YADXX:1:1101:1914:2223 1:N:0:TCTTAACTGG+TTCAGGCCGA
    
    // Extract information from SRA header
    const char* space_pos = strchr(sra_header + 1, ' ');
    if (!space_pos) {
        // If no space found, return original header
        strcpy(illumina_header, sra_header);
        return illumina_header;
    }
    
    // Extract Illumina instrument information (e.g., HWI-ST808:130:H0B8YADXX:1:1101:1914:2223)
    char illumina_info[MAX_LINE_LENGTH];
    const char* length_pos = strstr(space_pos + 1, " length=");
    if (length_pos) {
        // Copy up to "length="
        int len = length_pos - (space_pos + 1);
        strncpy(illumina_info, space_pos + 1, len);
        illumina_info[len] = '\0';
    } else {
        // If no length found, copy everything
        strcpy(illumina_info, space_pos + 1);
    }
    
    // Remove trailing /1 or /2 from illumina_info
    char* slash_pos = strrchr(illumina_info, '/');
    if (slash_pos && (strcmp(slash_pos, "/1") == 0 || strcmp(slash_pos, "/2") == 0)) {
        *slash_pos = '\0';  // Remove /1 or /2
    }
    
    // Format as Illumina header
    // Format: @<instrument>:<run_id>:<flowcell_id>:<lane>:<tile>:<x>:<y> <read>:<filtered>:<control>:<index>
    snprintf(illumina_header, MAX_LINE_LENGTH, "@%s %d:N:0:%s", 
             illumina_info, read_number, DEFAULT_INDEX);
    
    return illumina_header;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input.fastq.gz>\n", argv[0]);
        fprintf(stderr, "Converts SRA format to Illumina format with index sequences\n");
        return 1;
    }
    
    // Open gzip file
    gzFile input_file = gzopen(argv[1], "rb");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int read_number = 1;  // Read number (1 or 2 for paired-end)
    
    // FastQ files have 4-line sets (read name, sequence, +, quality)
    while (gzgets(input_file, line, MAX_LINE_LENGTH) != NULL) {
        line_number++;
        
        // Remove newline character
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Process based on FastQ line number
        int position_in_record = (line_number - 1) % 4;
        
        switch (position_in_record) {
            case 0: // Read name line (starts with @)
                if (line[0] == '@') {
                    // Convert SRA format to Illumina format
                    // Detect read number from filename (_R1.fastq.gz = 1, _R2.fastq.gz = 2)
                    if (strstr(argv[1], "_R2.") || strstr(argv[1], "_2.")) {
                        read_number = 2;
                    } else {
                        read_number = 1;
                    }
                    
                    char* illumina_header = convert_to_illumina_format(line, read_number);
                    printf("%s\n", illumina_header);
                } else {
                    // If doesn't start with @, output as is
                    printf("%s\n", line);
                }
                break;
                
            case 1: // Sequence line
                printf("%s\n", line);
                break;
                
            case 2: // + line
                printf("%s\n", line);
                break;
                
            case 3: // Quality line
                printf("%s\n", line);
                break;
        }
    }
    
    // Close file
    if (gzclose(input_file) != Z_OK) {
        fprintf(stderr, "Error: Failed to close input file\n");
        return 1;
    }
    
    return 0;
}
