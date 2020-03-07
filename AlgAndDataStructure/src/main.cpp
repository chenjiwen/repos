#include <iostream>
#include <string>
#include "sort.h"
using namespace std;

#include "PriorQueue.h"
#include "stack.h"
#include "btree.h"



//extern void heap_sort_test(int array[], int len);
extern int josephus_game();
extern LinkList_T* josephus_game(int N, int M);
extern void print_cut_rod_solution();
extern bool isPossibleDivide(int array[], int len, int k);

void heap_sort_test(int array[], int len) {
	vector<int> vec;
	BinaryHeap bHeap;
	int idx = 0;

	cout << "heap sort test" << endl;

	for (idx = 0; idx < len; idx++)
	{
		vec.push_back(array[idx]);
	}

	bHeap = BinaryHeap(vec);
	bHeap.heap_sort();


	cout << "heap sort end" << endl;
}

void btree_test() {

}

void avltree_test() {
	//BTreeElemType elem[] = {4, 2, 8, 1, 3, 7, 9, 5, 6};
	BTreeElemType elem[] = { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 9, 8};
	vector<BTreeElemType> elem_vec(elem, elem + sizeof(elem)/sizeof(elem[0]));
	AVLTree AVLtree(elem_vec);
	AVLTree* pAVLTObj = NULL;

	pAVLTObj = new AVLTree(elem_vec);
	/*
	 *当显式调用析构函数释放资源和对象时，父类/祖先类的析构函数都会被依次调用
	 */
	//pAVLTObj->~AVLTree();
	//调用delete的时候会自动调用析构函数
	//AVLTree::operator delete(pAVLTObj);
	delete pAVLTObj;
	//AVLtree.AVLTreeDelete(8);
}

extern LinkList_T* removeNthFromEnd(LinkList_T* head, int n);
extern LinkList_T* list_swap_pairs(LinkList_T* head);
extern LinkList_T* reverseKGroup(LinkList_T* head, int k);

void linklist_test() {
	LinkListEmemType elem_a[] = { 1, 2, 3, 4, 5};
	LinkListEmemType elem_b[] = {3,3,4,5,5,6,8,9};
	LinkListEmemType elem_c[] = { 1 };
	LinkList_T* pListHead_a = NULL;
	LinkList_T* pListHead_b = NULL;
	LinkList_T* pListHead_c = NULL;
	LinkList_T* pListHead_i = NULL;
	LinkList_T* pListHead_u = NULL;

	for (uint32_t i = 0; i < sizeof(elem_a)/sizeof(elem_a[0]); i++)
	{
		list_add(pListHead_a, elem_a[i]);
	}

	for (uint32_t i = 0; i < sizeof(elem_b) / sizeof(elem_b[0]); i++)
	{
		list_add(pListHead_b, elem_b[i]);
	}

	for (uint32_t i = 0; i < sizeof(elem_c) / sizeof(elem_c[0]); i++)
	{
		list_add(pListHead_c, elem_c[i]);
	}

	//pListHead_c = removeNthFromEnd(pListHead_c, 2);
	pListHead_c = list_swap_pairs(pListHead_c);

	pListHead_i = list_intersection(pListHead_a, pListHead_b);
	pListHead_u = list_union(pListHead_a, pListHead_b);
	//list_reverse(pListHead_a, &pListHead_a);
	pListHead_a = reverseKGroup(pListHead_a, 2);
	//list_reverse(pListHead);

}

extern bool isPossibleDivide(vector<int>& nums, int k);
extern void test_lcs();
extern void bst_test();
extern void optBst_test();
extern void knapsack_test();
extern void BBTreeTest();
extern void BPTree_test();
extern void dlist_test();
extern void BNTreeTest();
extern void BNHeapTest();
extern void graphic_test();
extern void graph_test();

int main(int argc, char **argv) {
	uint32_t array_a[5] = {1, 2, 3, 4, 5};
	uint32_t array_b[5] = {7, 8, 6, 10, 9};
	//uint32_t array[10];
	uint32_t elem = 0;
	int idx = 0;
	const int j = idx;
	//r1是一个const 对象的引用，不能通过r1来修改const对象
	const int& r1 = idx;
	int& r2 = idx;
	idx++;
	r2++;
	//int num_array[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int num_array[5] = { -1, -2, -3, -4, -5 };
	//linklist_test();
	int record[2];
	int max_subseq_sum = 0;
	int array_heap[10] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
	uint32_t array[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
	BTreeElemType elem_array[] = {'a','b','+','c','d','e','+','*','*'};
	BTreeElemType elem_array_post[] = { 'a','b','c','*','+','d','e','*','f','+','g','*','+' };
	BTreeElemType elem_array_bstree[] = { 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 };
	vector<int> vect(array_heap, array_heap + 10);
	vector<int>::size_type size = 0;
	vector<int>::size_type vidx = 0;
	BinaryHeap bheap(array_heap, 10);
	cout << "tree inorder traverse:" << endl;
	ExprTree exprTree(elem_array, 9);
	exprTree.btree_inorder_traverse();
	cout << "\n tree postorder traverse:" << endl;
	ExprTree exprtPost(elem_array_post, 13);
	exprtPost.btree_postorder_traverse_non_recursive();
	cout << "\n Height of tree: " << exprtPost.btree_height() << endl;
	//exprTree.build_expr_tree_postorder(elem_array, 9);
	//exprTree.btree_inorder_traverse_non_recursive(exprTree.get_root());
	BSTree bstee(elem_array_bstree, 11);
	bstee.btree_inorder_traverse();

	BTreeElemType RBTreeElemArray[] = { 41, 38, 31, 12, 19, 8 };
	BTreeElemType RBTreeDelElemArray[] = { 8, 12, 19, 31, 38, 41 };
	RBTree rbtree(RBTreeElemArray,6);

	BTreeNode* pNode = NULL;
	for (int i = 0; i < 6; i++)
	{
		pNode = rbtree.BSTree_search(RBTreeDelElemArray[i]);
		rbtree.RBTreeDelete(pNode);
		delete pNode;
	}

	int array_c[] = {3,2,1,2,3,4,3,4,5,9,10,11};

	//isPossibleDivide(array_c, sizeof(array_c)/sizeof(array_c[0]), 3);
	vector<int> nums(array_c, array_c + sizeof(array_c) / sizeof(array_c[0]));
	//isPossibleDivide(nums, 3);

	//avltree_test();

	//bst_test();

	//test_lcs();

	//knapsack_test();

	//optBst_test();
	//BNTreeTest();
	//BNHeapTest();
	//dlist_test();
	//BBTreeTest();
	//BPTree_test();

	//graphic_test();
	graph_test();
	bheap.dump_heap();

	elem = select_kth(2, 0, 9, array);

	//elem = select_kth_with_heap(5);

	josephus_game(5, 2)->elem;

	print_cut_rod_solution();

	//PriorityQueue  PrioQueue;
	//PriorityQueue  PriQue(array_heap, 10);
	PriorityQueue MinSmallPrioQue(vect);
	MinSmallPrioQue.min_heap_sort();
	//PriQue.PriorityQueueIncreasePriority(9, 15);
	//PriQue.PriorityQueueDelete(2);
	//vect = bheap.getHeapContent();
	//vect.push_back(0x80000001);

	//heap_sort_test(array_heap, 10);
	//bheap.max_heapify(2,1);
	//bheap.build_max_heap();

	string str("abca");
	string s;

	cout << "find:" << str.find('a') << " rfind:" << str.rfind('a') << endl;

	reverse(str.begin(), str.end());
	cout << str << endl;

	//str = "ibvjkmpyzsifuxcabqqpahjdeuzaybqsrsmbfplxycsafogotliyvhxjtkrbzqxlyfwujzhkdafhebvsdhkkdbhlhmaoxmbkqiwiusngkbdhlvxdyvnjrzvxmukvdfobzlmvnbnilnsyrgoygfdzjlymhprcpxsnxpcafctikxxybcusgjwmfklkffehbvlhvxfiddznwumxosomfbgxoruoqrhezgsgidgcfzbtdftjxeahriirqgxbhicoxavquhbkaomrroghdnfkknyigsluqebaqrtcwgmlnvmxoagisdmsokeznjsnwpxygjjptvyjjkbmkxvlivinmpnpxgmmorkasebngirckqcawgevljplkkgextudqaodwqmfljljhrujoerycoojwwgtklypicgkyaboqjfivbeqdlonxeidgxsyzugkntoevwfuxovazcyayvwbcqswzhytlmtmrtwpikgacnpkbwgfmpavzyjoxughwhvlsxsgttbcyrlkaarngeoaldsdtjncivhcfsaohmdhgbwkuemcembmlwbwquxfaiukoqvzmgoeppieztdacvwngbkcxknbytvztodbfnjhbtwpjlzuajnlzfmmujhcggpdcwdquutdiubgcvnxvgspmfumeqrofewynizvynavjzkbpkuxxvkjujectdyfwygnfsukvzflcuxxzvxzravzznpxttduajhbsyiywpqunnarabcroljwcbdydagachbobkcvudkoddldaucwruobfylfhyvjuynjrosxczgjwudpxaqwnboxgxybnngxxhibesiaxkicinikzzmonftqkcudlzfzutplbycejmkpxcygsafzkgudy";
	//str = "babad";
	str = "abccccdd";
	//str = "cbbd";
	//str = "jrjnbctoqgzimtoklkxcknwmhiztomaofwwzjnhrijwkgmwwuazcowskjhitejnvtblqyepxispasrgvgzqlvrmvhxusiqqzzibcyhpnruhrgbzsmlsuacwptmzxuewnjzmwxbdzqyvsjzxiecsnkdibudtvthzlizralpaowsbakzconeuwwpsqynaxqmgngzpovauxsqgypinywwtmekzhhlzaeatbzryreuttgwfqmmpeywtvpssznkwhzuqewuqtfuflttjcxrhwexvtxjihunpywerkktbvlsyomkxuwrqqmbmzjbfytdddnkasmdyukawrzrnhdmaefzltddipcrhuchvdcoegamlfifzistnplqabtazunlelslicrkuuhosoyduhootlwsbtxautewkvnvlbtixkmxhngidxecehslqjpcdrtlqswmyghmwlttjecvbueswsixoxmymcepbmuwtzanmvujmalyghzkvtoxynyusbpzpolaplsgrunpfgdbbtvtkahqmmlbxzcfznvhxsiytlsxmmtqiudyjlnbkzvtbqdsknsrknsykqzucevgmmcoanilsyyklpbxqosoquolvytefhvozwtwcrmbnyijbammlzrgalrymyfpysbqpjwzirsfknnyseiujadovngogvptphuyzkrwgjqwdhtvgxnmxuheofplizpxijfytfabx";
	s = longestPalindrome(str);

	//bubble_sort(5, array);
	//insertion_sort(5, array);
	//bubble_sort(5, array_a);
	//insertion_sort(5, array_b);
	//merge_sorted(array, 5, array_a, 5, array_b);
	//merge_sort(5, array_a);
	//merge_sort(5, array_b);

	//quick_sort(0, 4, array_a);

	//selecion_sort(5, array_a);

	max_subseq_sum = find_max_sum_subsequence(num_array, 0, 4, record);

	cout << "max sum of subsequence is " << max_subseq_sum << ", from: " << record[0] << " to " << record[1] << endl;

	cout << "sorted array:" << endl;
	for (idx = 0; idx < sizeof(array_a)/sizeof(array_a[0]); idx++)
	{
		cout << array_a[idx] << " ";
	}
	cout << endl;


	return 0;
}