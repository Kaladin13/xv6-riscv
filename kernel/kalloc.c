// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

#define MAX_COW_PAGES 65536

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

struct {
  ushort ref_count;
  uint64 pa;
} blocked_pages[MAX_COW_PAGES] = {{0, 0}};

ushort* get_ref(uint64 pa) {
  for (int i = 0; i < MAX_COW_PAGES; i++) {
    if (blocked_pages[i].pa == pa) {
      return &blocked_pages[i].ref_count;
    }
  }
  
  return 0;
}

int create_page_count(uint64 pa) {
  for (int i = 0; i < MAX_COW_PAGES; i++) {
    if (blocked_pages[i].pa == 0) {
      blocked_pages[i].pa = pa;
      blocked_pages[i].ref_count = 2;

      return 0;
    }
  }

  return -1;
}

void free_page_count(uint64 pa) {
  for (int i = 0; i < MAX_COW_PAGES; i++) {
    if (blocked_pages[i].pa == pa) {
      blocked_pages[i].pa = 0;
      blocked_pages[i].ref_count = 0;
      return;
    }
  }
}

void
kinit()
{
  char* p = (char*)PGROUNDUP((uint64)end);
  bd_init(p, (void*)PHYSTOP);
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void kfree(void *pa) { bd_free(pa); }

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *kalloc(void) { return bd_malloc(PGSIZE); }
