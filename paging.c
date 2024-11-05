#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096  // Define the size of a page (4KB)

typedef struct {
    int frame_number;
    int valid;
} PageTableEntry;

typedef struct {
    PageTableEntry *entries;
    int size;
} PageTable;

PageTable* create_page_table(int num_pages) {
    PageTable *page_table = (PageTable *)malloc(sizeof(PageTable));
    page_table->size = num_pages;
    page_table->entries = (PageTableEntry *)malloc(sizeof(PageTableEntry) * num_pages);

    int i;
    for (i = 0; i < num_pages; i++) {
        page_table->entries[i].frame_number = -1; // Invalid frame initially
        page_table->entries[i].valid = 0;         // Page not in memory
    }

    return page_table;
}

void map_page(PageTable *page_table, int page_number, int frame_number) {
    if (page_number >= 0 && page_number < page_table->size) {
        page_table->entries[page_number].frame_number = frame_number;
        page_table->entries[page_number].valid = 1;
    } else {
        printf("Invalid page number\n");
    }
}

int get_frame(PageTable *page_table, int page_number) {
    if (page_number >= 0 && page_number < page_table->size && page_table->entries[page_number].valid) {
        return page_table->entries[page_number].frame_number;
    } else {
        printf("Page fault or invalid page number\n");
        return -1; // Indicates page fault or invalid page
    }
}

void free_page_table(PageTable *page_table) {
    free(page_table->entries);
    free(page_table);
}

int main() {
    int num_pages, i, page_number, frame_number, num_mappings;

    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    PageTable *page_table = create_page_table(num_pages);

    printf("Enter the number of mappings: ");
    scanf("%d", &num_mappings);

    for (i = 0; i < num_mappings; i++) {
        printf("Enter page number and frame number for mapping %d: ", i + 1);
        scanf("%d %d", &page_number, &frame_number);
        map_page(page_table, page_number, frame_number);
    }

    printf("Enter the page number to access: ");
    scanf("%d", &page_number);
    printf("Frame for page %d: %d\n", page_number, get_frame(page_table, page_number));

    free_page_table(page_table);
    return 0;
}

