#include <iostream>
#include <string>
#include "sort.h"
using namespace std;

#include "PriorQueue.h"
#include "stack.h"
#include "btree.h"



//extern void heap_sort_test(int array[], int len);

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

int main(int argc, char **argv) {
	uint32_t array_a[5] = {1, 2, 3, 4, 5};
	uint32_t array_b[5] = {7, 8, 6, 10, 9};
	//uint32_t array[10];
	uint32_t elem = 0;
	int idx = 0;
	//int num_array[16] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int num_array[5] = { -1, -2, -3, -4, -5 };
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
	RBTree rbtree(RBTreeElemArray,6);

	bheap.dump_heap();

	elem = select_kth(2, 0, 9, array);

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
	str = "abcddcbe";
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