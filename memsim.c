#include <stdio.h>
#include <string.h>
#include "circularList.c"
typedef struct {
        int pageNo;
        int modified;
		int refBit;
} page;

//pageTable
typedef struct{
	page * entries;
	int size;
	Queue * q;
	Circle * c;
} pageTable;
//global page table pointer
pageTable * table;


enum    repl { random, fifo, lru, clock};
int     createMMU( int);
int     checkInMemory( int ) ;
int     allocateFrame( int ) ;
page    selectVictim( int, enum repl) ;
const   int pageoffset = 12;            /* Page size is fixed to 4 KB */
int     numFrames ;

/* Creates the page table structure to record memory allocation */
int     createMMU (int frames)
{

        // to do

		//allocate space for Page Table
		table = (pageTable *)malloc(sizeof(pageTable));
		//error handling for malloc
		if (table == NULL){
			perror("Failed to create Page Table");
			exit(-1);
		}
		//allocate space for table entries
		table->entries = (page * )malloc(frames * sizeof(page));
		//error handling for malloc
		if (table->entries == NULL){
			perror("Failed to allocate memory for page entries");
			//prevent memory leak
			free(table);
			exit(-1);
		}
		//allocate correct table size
		table->size = frames;
		table->q = createQueue();
		table->c = createCircle();
		for (int i = 0; i < frames; i++){
			table->entries[i].pageNo = -1; //indicates that is not allocated
			table->entries[i].modified = 0;
			table->entries[i].refBit = 0;
		}


        return 0;
}

/* Checks for residency: returns frame no or -1 if not found */
int     checkInMemory( int page_number)
{

        // to do
		//error handling
		if (table != NULL && table->entries != NULL){
			//loop through table
			for (int i = 0; i < table->size; i++){
				//if found in memory return address in pagetable
				if (table->entries[i].pageNo == page_number){
					return i;
					//return found entry
				}
			}
			//return result (in this case negative 1)
			return -1;
		} else {
			//exit if accessed before MMU/Page table allocated
			perror("MMU/Page Table not initialised!");
			exit(-1);
			return -1;
		}
		//will never reach this....
        return -1;
}

/* allocate page to the next free frame and record where it put it */
int     allocateFrame( int page_number)
{
        // to do
		//check that is allocated
		if (table != NULL && table->entries != NULL){
			//loop through the table
			for (int i = 0; i < table->size; i++){
				//check if page is unallocated
				if (table->entries[i].pageNo == -1){
					//update values
					table->entries[i].pageNo = page_number;
					table->entries[i].modified = 0;
					table->entries[i].refBit = 0;
					//return iterator to it
					return i;
				}
			}
			return -1;
		} else {
			perror("MMU/Page Table not initialised!");
			exit(-1);
			return -1;
		}

}

/* Selects a victim for eviction/discard according to the replacement algorithm,  returns chosen frame_no  */
page    selectVictim(int page_number, enum repl  mode )
{
        page    victim;
        // to do 
        victim.pageNo = 0;
        victim.modified = 0;
		int victimIndex;
		//Simple LRU for now
		//will add handling to check mode later
		switch (mode){
				case fifo:
				case lru:
					victimIndex = dequeue(table->q);
					victim = table->entries[victimIndex];
					break;
				case random:
					srand(time(NULL));
					victimIndex = rand() % numFrames;
					victim = table->entries[victimIndex];
					break;
				case clock:

					if (table->c->curr != NULL){

						while (table->entries[table->c->curr->data].refBit != 0){
							table->entries[table->c->curr->data].refBit = 0;
							rotate(table->c);
						}
						victimIndex = table->c->curr->data;
						victim = table->entries[victimIndex];
						rotate(table->c);

					} else {
						printf("Error curr is NULL \n");

						exit(-1);
					}
					break;
				default:
					victim.pageNo = -1;
					victim.modified = 0;
					break;	
		}
		table->entries[victimIndex].pageNo = page_number;
		table->entries[victimIndex].modified = 0;
		table->entries[victimIndex].refBit = 0;
        return (victim) ;


}

void rotateAndSetBits(Circle * c, int data){
	if (c->curr->data != data){
		rotate(c);
	} else {
		return;
	}
	while (c->curr->data != data){
		table->entries[c->curr->data].refBit = 0;
        c->curr = c->curr->next;
        c->tail = c->tail->next;
    }

}
		
main(int argc, char *argv[])
{
  
	char	*tracename;
	int	page_number,frame_no, done ;
	int	do_line, i;
	int	no_events, disk_writes, disk_reads;
	int     debugmode;
 	enum	repl  replace;
	int	allocated=0; 
	int	victim_page;
        unsigned address;
    	char 	rw;
	page	Pvictim;
	FILE	*trace;


        if (argc < 5) {
             printf( "Usage: ./memsim inputfile numberframes replacementmode debugmode \n");
             exit ( -1);
	}
	else {
        tracename = argv[1];	
	trace = fopen( tracename, "r");
	if (trace == NULL ) {
             printf( "Cannot open trace file %s \n", tracename);
             exit ( -1);
	}
	numFrames = atoi(argv[2]);
        if (numFrames < 1) {
            printf( "Frame number must be at least 1\n");
            exit ( -1);
        }
        if (strcmp(argv[3], "lru\0") == 0)
            replace = lru;
	    else if (strcmp(argv[3], "rand\0") == 0)
	     replace = random;
	          else if (strcmp(argv[3], "clock\0") == 0)
                       replace = clock;		 
	               else if (strcmp(argv[3], "fifo\0") == 0)
                             replace = fifo;		 
        else 
	  {
             printf( "Replacement algorithm must be rand/fifo/lru/clock  \n");
             exit ( -1);
	  }

        if (strcmp(argv[4], "quiet\0") == 0)
            debugmode = 0;
	else if (strcmp(argv[4], "debug\0") == 0)
            debugmode = 1;
        else 
	  {
             printf( "Replacement algorithm must be quiet/debug  \n");
             exit ( -1);
	  }
	}
	
	done = createMMU (numFrames);
	if ( done == -1 ) {
		 printf( "Cannot create MMU") ;
		 exit(-1);
        }
	no_events = 0 ;
	disk_writes = 0 ;
	disk_reads = 0 ;

        do_line = fscanf(trace,"%x %c",&address,&rw);
	while ( do_line == 2)
	{
		page_number =  address >> pageoffset;
		frame_no = checkInMemory( page_number) ;    /* ask for physical address */
		if ( frame_no == -1 )
		{
		  disk_reads++ ;			/* Page fault, need to load it into memory */
		  if (debugmode) 
		      printf( "Page fault %8d \n", page_number) ;
		  if (allocated < numFrames)  			/* allocate it to an empty frame */ {
                     frame_no = allocateFrame(page_number);
		     		 allocated++;
            } else {

		      Pvictim = selectVictim(page_number, replace) ;   /* returns page number of the victim  */
		      frame_no = checkInMemory( page_number) ;    /* find out the frame the new page is in */
			  if (Pvictim.modified)           /* need to know victim page and modified  */ {
			    disk_writes++;
			    if (debugmode) printf( "Disk write %8d \n", Pvictim.pageNo) ;
		      } else if (debugmode) printf( "Discard    %8d \n", Pvictim.pageNo) ;
		    }
		}
		if (replace == lru){
			enqueue(table->q, frame_no);
		} else if (replace == clock){
			insertNode(table->c, frame_no);
			table->entries[frame_no].refBit = 1;
		}
		if ( rw == 'R'){

			
		    if (debugmode) printf( "reading    %8d \n", page_number) ;
		} else if ( rw == 'W'){


			table->entries[checkInMemory(page_number)].modified = 1;
		    // mark page in page table as written - modified
		    if (debugmode) printf( "writting   %8d \n", page_number) ;
		}
		 else {
		      printf( "Badly formatted file. Error on line %d\n", no_events+1); 
		      exit (-1);
		}
		
		no_events++;
        	do_line = fscanf(trace,"%x %c",&address,&rw);
	}

	/*printf( "total memory frames:  %d\n", numFrames);
	printf( "events in trace:      %d\n", no_events);
	printf( "total disk reads:     %d\n", disk_reads);
	printf( "total disk writes:    %d\n", disk_writes);
	printf( "page fault rate:      %.4f\n", (float) disk_reads/no_events);*/
	printf( "%d, %.6f\n", numFrames, (float) disk_reads/no_events);
}
				
