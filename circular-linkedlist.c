/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>1
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;  //왼쪽 노드의 주소를 저장할 링크필드 
	struct Node* rlink;  //오른쪽 노드의 주소를 저장할 링크필드
} listNode;  //노드 구조체, 

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;  //헤드노드 = null 초기화

	printf("[----- [HanSeungheon] [%d] -----]\n", 2020023057);

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); // 헤드포인터 메모리 동적 할당
	(*h)->rlink = *h;  // 공백으로 만들기
	(*h)->llink = *h;  // 공백으로 만들기
	(*h)->key = -9999;  
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h) //리스트가 비었다면
	{
		free(h);  //h메모리 해제
		return 1;
	}

	listNode* p = h->rlink;  //헤드노드의 r링크 대입

	listNode* prev = NULL;  //이전 노드 포인터에 널 값 초기화
	while(p != NULL && p != h) { //반복문을 통한 매모리 해제
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);  //매모리 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //리스트가 비었다면
		printf("Nothing to print....\n");  //출력할 게 없음
		return;
	}

	p = h->rlink;  

	while(p != NULL && p != h) {  //출력 반복문
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 생성 및 메모리 할당
	node->key = key; //입력받은 키 값 저장
	node->rlink = NULL;  //r링크 null 초기화
	node->llink = NULL;  //l링크 null 초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */
	{
		h->rlink = node;  // 헤드노드가 첫 노드를 포인팅하게 만든다
		h->llink = node;  // 헤드노드가 첫 노드를 포인팅하게 만든다
		node->rlink = h;  // 해당 노드 외의 노드가 없으므로 노드가 헤드노드를 가리키게 만든다
		node->llink = h;  // 노드가 헤드노드를 가리키게 만든다
	} else {
		h->llink->rlink = node;  //헤드노드가 뉴노드를 가리키게 된다
		node->llink = h->llink;  // 노드가 헤드노드의 l링크를 가리키게 한다.
		h->llink = node;  //헤드노드의 l링크가 노드를 가리키게 한다
		node->rlink = h;  // 노드의 r링크가 헤드노드를 가리키게 한다. 연결 완료.
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)  //리스트가 비었다면
	{
		printf("nothing to delete.\n"); //지울게 없음
		return 1;
	}

	listNode* nodetoremove = h->llink;  

	/* link 정리 */
	nodetoremove->llink->rlink = h;  // 자기자신을 가리키게 만든다
	h->llink = nodetoremove->llink; 

	free(nodetoremove);  // 할당했던 메모리 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //노드 생성 및 메모리 할당
	node->key = key;  //입력받은 키값 대입
	node->rlink = NULL;  // r링크 초기화
	node->llink = NULL;  // l링크 초기화


	node->rlink = h->rlink;  // 헤드노드와 노드 연결
	h->rlink->llink = node;  
	node->llink = h;  
	h->rlink = node;  


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)  //프리컨디션 조사 
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;  

	/* link 정리 */
	nodetoremove->rlink->llink = h;  // 뒤 노드의 링크 변환
	h->rlink = nodetoremove->rlink;  

	free(nodetoremove);  //메모리 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) {  //프리컨디션 조사
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;  

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;

	while(n != NULL && n != h){  //반복문을 통해 노드 순서 스왑
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->rlink = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 생성 및 메모리 할당
	node->key = key;  // 
	node->llink = node->rlink = NULL;

	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)  //프리컨디션 조사
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //함수 호출
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);  //함수호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;  //연결된 링크 변경
				free(n);  //메모리 해제
			}
			return 0;
		}

		n = n->rlink;  
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


