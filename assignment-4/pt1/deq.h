#define TYPE double

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

/* Deque based on Circularly-Doubly-Linked List WITH Sentinel */
struct Deque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};

void initDeque(struct Deque *q);
int isEmptyDeque(struct Deque *q);
void addBackDeque(struct Deque *q, TYPE val);
void addFrontDeque(struct Deque *q, TYPE val);
TYPE frontDeque(struct Deque *q);
TYPE backDeque(struct Deque *q);
void removeFrontDeque(struct Deque *q);
void removeBackDeque(struct Deque *q);
void freeDeque(struct Deque *q);
void printDeque(struct Deque *q);


