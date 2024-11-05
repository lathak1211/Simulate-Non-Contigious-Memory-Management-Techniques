#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int base;
    int limit;
} SegmentTableEntry;

typedef struct {
    SegmentTableEntry *entries;
    int size;
} SegmentTable;

SegmentTable* create_segment_table(int num_segments) {
    SegmentTable *segment_table = (SegmentTable *)malloc(sizeof(SegmentTable));
    segment_table->size = num_segments;
    segment_table->entries = (SegmentTableEntry *)malloc(sizeof(SegmentTableEntry) * num_segments);

    int i;
    for (i = 0; i < num_segments; i++) {
        segment_table->entries[i].base = -1;  // Invalid base address initially
        segment_table->entries[i].limit = 0;  // Zero limit initially
    }

    return segment_table;
}

void map_segment(SegmentTable *segment_table, int segment_number, int base, int limit) {
    if (segment_number >= 0 && segment_number < segment_table->size) {
        segment_table->entries[segment_number].base = base;
        segment_table->entries[segment_number].limit = limit;
    } else {
        printf("Invalid segment number\n");
    }
}

int translate_address(SegmentTable *segment_table, int segment_number, int offset) {
    if (segment_number >= 0 && segment_number < segment_table->size) {
        SegmentTableEntry entry = segment_table->entries[segment_number];
        if (offset >= 0 && offset < entry.limit) {
            return entry.base + offset;
        } else {
            printf("Offset out of bounds\n");
            return -1; // Indicates invalid offset
        }
    } else {
        printf("Invalid segment number\n");
        return -1; // Indicates invalid segment
    }
}

void free_segment_table(SegmentTable *segment_table) {
    free(segment_table->entries);
    free(segment_table);
}

int main() {
    int num_segments, i, segment_number, base, limit, offset, num_mappings;

    printf("Enter the number of segments: ");
    scanf("%d", &num_segments);

    SegmentTable *segment_table = create_segment_table(num_segments);

    printf("Enter the number of mappings: ");
    scanf("%d", &num_mappings);

    for (i = 0; i < num_mappings; i++) {
        printf("Enter segment number, base, and limit for mapping %d: ", i + 1);
        scanf("%d %d %d", &segment_number, &base, &limit);
        map_segment(segment_table, segment_number, base, limit);
    }

    printf("Enter the segment number and offset to access: ");
    scanf("%d %d", &segment_number, &offset);
    printf("Physical address for segment %d, offset %d: %d\n", segment_number, offset, translate_address(segment_table, segment_number, offset));

    free_segment_table(segment_table);
    return 0;
}

