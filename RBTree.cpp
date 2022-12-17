#include "RBTree.h"
//=======CAC HAM HO TRO============
void set_Color(int colorBackground, int colorText) {
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, colorBackground * 16 + colorText);
}
/* Hoán vị màu (Color) */
void swapColors(EColor& color1, EColor& color2)
{
	EColor temp = color1;
	color1 = color2;
	color2 = temp;
}
/* Hoán vị giá trị */
void swapInfos(ItemType& info1, ItemType& info2)
{
	ItemType temp = info1;
	info1 = info2;
	info2 = temp;
}
//cap phat node

Node* createNode(ItemType x)
{
	Node* p = new Node;
	p->Info = x; // Gán dữ liệu mới cho nút
	p->Color = RED; // Gán màu đỏ (Red) mặc định
	p->Left = NULL; // Chưa có nút con trái
	p->Right = NULL; // Chưa có nút con phải
	p->Parent = NULL; // Chưa có nút cha
	return p;
}
//ham xuat 1 node
void showNode(Node* p)
{
	if (p->Color == RED)
		set_Color(15, 12); //Light Red=12 (C), Bright White=15 (F)
	else if (p->Color == BLACK)
		set_Color(15, 0); //Black=0, Bright White=15 (F)
	xuatSV(p->Info);
	set_Color(14, 2); //Light Yellow=14 (E), Green=2
}
//ham khoi tao
void initBRTree(Node*& root)
{
	root = NULL;
}
/* Một hàm đệ quy để thực hiện việc duyệt thứ tự LNR - InOrder */
void showBRTree_InOrder(Node* root)
{
	if (root == NULL) return;
	showBRTree_InOrder(root->Left);
	showNode(root);// xuat sinh vien
	showBRTree_InOrder(root->Right);
}
//=============================INSERTION=============================
/* Ham Them nhu cay nhi phan tim kiem*/
Node* BRTInsert(Node* root, Node* pNew)
{
	/* Nếu cây trống thì trả về một Node mới */
	if (root == NULL) return pNew;
	/* Nếu không thì tiếp tục duyệt xuống dưới cây */
	if (compare(pNew->Info, root->Info) < 0)
	{
		root->Left = BRTInsert(root->Left, pNew);
		root->Left->Parent = root;
	}
	else if (compare(pNew->Info, root->Info) > 0)
	{
		root->Right = BRTInsert(root->Right, pNew);
		root->Right->Parent = root;
	}

	/* Trả về con trỏ Node */
	return root;
}
/* Thuật toán xoay trái */
void rotateLeft(Node*& root, Node*& p)
{
	Node* pRight = p->Right;
	p->Right = pRight->Left;
	if (p->Right != NULL)
		p->Right->Parent = p;
	pRight->Parent = p->Parent;
	if (p->Parent == NULL)
		root = pRight;
	else if (p == p->Parent->Left)
		p->Parent->Left = pRight;
	else
		p->Parent->Right = pRight;
	pRight->Left = p;
	p->Parent = pRight;
}
/* Thuật toán xoay phải */
void rotateRight(Node*& root, Node*& p)
{
	Node* pLeft = p->Left;
	p->Left = pLeft->Right;
	if (p->Left != NULL)
		p->Left->Parent = p;
	pLeft->Parent = p->Parent;
	if (p->Parent == NULL)
		root = pLeft;
	else if (p == p->Parent->Left)
		p->Parent->Left = pLeft;
	else
		p->Parent->Right = pLeft;
	pLeft->Right = p;
	p->Parent = pLeft;
}
/* Sửa lại cấu trúc khi chèn Node vào hoặc xóa node */
void fixViolation(Node*& root, Node*& pt)
{
	Node* pParent = NULL;

	Node* pGrandParent = NULL;
	if (!pt || !pt->Parent) return; //Nút rỗng thì dừng
	while ((pt != root) && (pt->Color != BLACK) && (pt->Parent->Color == RED))
	{
		pParent = pt->Parent;
		pGrandParent = pt->Parent->Parent; //Nút ông
		if (!pGrandParent) break; //Nút ông bị rỗng
		/* Trường hợp A:
		node cha của pt là con trái của node ông của pt */
		if (pParent == pGrandParent->Left)
		{
			Node* pUncle = pGrandParent->Right;
			/* Trường hợp: 1
			node chú của pt là node đỏ khi này chỉ cần đổi màu cho node đó

			thành đen */

			if (pUncle != NULL && pUncle->Color == RED)
			{
				pGrandParent->Color = RED;
				pParent->Color = BLACK;
				pUncle->Color = BLACK;
				pt = pGrandParent;
			}
			else
			{
				/* Trường hợp: 2
				pt là node con phải của node cha nó ta thực hiện xoay trái

				*/

				if (pt == pParent->Right)
				{
					rotateLeft(root, pParent);
					pt = pParent;
					pParent = pt->Parent;
				}
				/* Trường hợp: 3
				pt là con trái của node cha nó ta thực hiện xoay phải */
				rotateRight(root, pGrandParent);
				swapColors(pParent->Color, pGrandParent->Color);
				pt = pParent;
			}
		}
		/* Trường hợp: B
		node cha của pt là con phải của node cha của pt */
		else
		{
			Node* pUncle = pGrandParent->Left;
			/* Trường hợp: 1
			node chú của pt là node đỏ khi này chỉ cần đổi màu cho node đó

			thành đen */

			if ((pUncle != NULL) && (pUncle->Color == RED))

			{
				pGrandParent->Color = RED;
				pParent->Color = BLACK;
				pUncle->Color = BLACK;
				pt = pGrandParent;
			}
			else
			{
				/* Trường hợp: 2
				pt là con trái của node cha nó ta thực hiện xoay phải */
				if (pt == pParent->Left)
				{
					rotateRight(root, pParent);
					pt = pParent;
					pParent = pt->Parent;
				}
				/* Trường hợp: 3
				pt là node con phải của node cha nó -> nên thực hiện xoay

				trái */

				rotateLeft(root, pGrandParent);
				swapColors(pParent->Color, pGrandParent->Color);
				pt = pParent;
			}
		}
	}
	root->Color = BLACK;
}
/* Chèn một node mới với dữ liệu đã cho */
void insert(Node*& root, ItemType Info)
{
	Node* pNew = createNode(Info);
	/* Thực hiện chèn như bình thường */
	root = BRTInsert(root, pNew);
	/* Sửa lại lỗi của quy tắc cây đỏ đen */
	fixViolation(root, pNew);
}
//=============================END-INSERTION=============================
//==================SEARCH===================
/* Tìm kiếm Node SV trên cây theo ma so*/
Node* search(Node* root, char x_ma[]) {
	Node* temp = root;
	while (temp != NULL) {
		if (strcmp(x_ma, temp->Info.ma) == 0) {
			return temp;
		}
		else if (strcmp(x_ma, temp->Info.ma) < 0) {
			temp = temp->Left;
		}
		else {
			temp = temp->Right;
		}

	}
	return NULL; //Không tìm thấy x trong cây
}
//==================END-SEARCH===================
//=============================DELETION=============================
/* Kiểm tra xem node hiện tại có phải là node con trái của node cha không */
bool isOnLeft(Node* p)
{
	return p == p->Parent->Left;
}
/* Trả về con trỏ tới node chú (Uncle) */
Node* findUncle(Node* p) {
	// Nếu không có node cha hoặc node ông, thì không có node chú
	if (p->Parent == NULL || p->Parent->Parent == NULL)
		return NULL;
	if (isOnLeft(p->Parent))
		// node chú bên phải
		return p->Parent->Parent->Right;
	else
		// node chú bên trái
		return p->Parent->Parent->Left;

}
/* Trả về con trỏ cho node anh chị em */
Node* findSibling(Node* p) {
	// node anh rỗng nếu không tồn tại node cha
	if (p->Parent == NULL)
		return NULL;
	if (isOnLeft(p))
		return p->Parent->Right;
	else
		return p->Parent->Left;

}
/* Tìm nút không có nút con bên trái trong cây con của nút đã cho */
Node* findSuccessor(Node* p) {
	Node* temp = p;
	while (temp->Left != NULL)
		temp = temp->Left;
	return temp;
}
/* Kiểm tra có node hiện tại có node con là nút đỏ hay không */
bool hasRedChild(Node* p) {
	return (p->Left != NULL && p->Left->Color == RED) ||
		(p->Right != NULL && p->Right->Color == RED);

}
/* Tìm nút thay thế nút đã xóa trong BST */
Node* BSTReplace(Node* p) {

	// Khi nút có 2 con
	if (p->Left != NULL && p->Right != NULL)
		return findSuccessor(p->Right);
	// Khi node lá
	if (p->Left == NULL && p->Right == NULL)
		return NULL;
	// Khi node có một con
	if (p->Left != NULL)
		return p->Left;
	else
		return p->Right;

}
void fixDoubleBlack(Node*& root, Node* p) {
	// p là node gốc thì return
	if (p == root) return;
	Node* pSibling = findSibling(p);
	Node* pParent = p->Parent;
	if (pSibling == NULL) {
		// Không có sibiling, màu đen kép được đẩy lên
		fixDoubleBlack(root, pParent);
	}
	else {
		if (pSibling->Color == RED) {
			// Anh chị em màu đỏ
			pParent->Color = RED;
			pSibling->Color = BLACK;
			if (isOnLeft(pSibling)) {
				// trường hợp left
				rotateRight(root, pParent);
			}
			else {
				// trường hợp right
				rotateLeft(root, pParent);
			}
			fixDoubleBlack(root, p);
		}
		else {
			// Anh chị em đen
			if (hasRedChild(pSibling)) {
				// Ist nhất 1 trẻ em màu đỏ
				if (pSibling->Left != NULL && pSibling->Left->Color == RED)

				{

					if (isOnLeft(pSibling)) {
						// left left
						pSibling->Left->Color = pSibling->Color;
						pSibling->Color = pParent->Color;
						rotateRight(root, pParent);
					}
					else {
						// right left
						pSibling->Left->Color = pParent->Color;
						rotateRight(root, pSibling);
						rotateLeft(root, pParent);
					}
				}

				else {
					if (isOnLeft(pSibling)) {
						// left right
						pSibling->Right->Color = pParent->Color;
						rotateLeft(root, pSibling);
						rotateRight(root, pParent);
					}
					else {
						// right right
						pSibling->Right->Color = pSibling->Color;
						pSibling->Color = pParent->Color;
						rotateLeft(root, pParent);
					}
				}
				pParent->Color = BLACK;
			}
			else {
				// Hai con đen
				pSibling->Color = RED;
				if (pParent->Color == BLACK)
					fixDoubleBlack(root, pParent);
				else
					pParent->Color = BLACK;

			}
		}
	}
}
/* Xóa nút đã cho */
void deleteNode(Node*& root, Node* pDelete) {
	Node* pReplace = BSTReplace(pDelete);
	// Đúng khi pReplace và pDelete đều đen
	bool flagDoubleBlack = ((pReplace == NULL || pReplace->Color == BLACK) &&
		(pDelete->Color == BLACK));
	Node* pParent = pDelete->Parent;
	if (pReplace == NULL) {
		// pReplace là NULL do đó pDelete là lá
		if (pDelete == root) {
			// pDelete là root, làm cho root là NULL
			root = NULL;
		}
		else {
			if (flagDoubleBlack) {
				// pReplace và pDelete đều đen
				// pDelete là lá, sửa màu đen kép tại pDelete
				fixDoubleBlack(root, pDelete);
			}
			else {
				// pReplace hoặc pDelete là đỏ
				if (findSibling(pDelete) != NULL)
					// node anh chị em không rỗng, làm cho nó màu đỏ
					findSibling(pDelete)->Color = RED;

			}
			// Xóa pDelete khỏi cây
			if (isOnLeft(pDelete)) {
				pParent->Left = NULL;

			}
			else {
				pParent->Right = NULL;
			}
		}
		delete pDelete;
		return;
	}
	if (pDelete->Left == NULL || pDelete->Right == NULL) {
		// pDelete có 1 node con
		if (pDelete == root) {
			// pDelete là gốc, gán giá trị của pReplace cho pDelete và xóa pReplace

			pDelete->Info = pReplace->Info;
			pDelete->Left = pDelete->Right = NULL;
			delete pReplace;
		}
		else {
			// Tách node pDelete khỏi cây và di chuyển node pReplace lên
			if (isOnLeft(pDelete)) {
				pParent->Left = pReplace;
			}
			else {
				pParent->Right = pReplace;
			}
			delete pDelete;
			pReplace->Parent = pParent;
			if (flagDoubleBlack) {
				// pReplace và pDelete đều đen, sửa hai màu đen ở pReplace
				fixDoubleBlack(root, pReplace);
			}
			else {
				// pReplace hoặc pDelete đỏ, màu pReplace đen
				pReplace->Color = BLACK;
			}
		}
		return;
	}
	// pDelete có 2 con, hoán đổi giá trị với nút kế nhiệm (thế mạng) và đệ quy
	swapInfos(pReplace->Info, pDelete->Info);
	deleteNode(root, pReplace);
}
/* chức năng tiện ích xóa nút có giá trị nhất định */
void deleteByInfo(Node*& root, char x_ma[]) {
	// BRTree là rỗng
	if (root == NULL) return;
	Node* delete_pt = search(root, x_ma);
	if (delete_pt == NULL) {
		printf("\nKhong tim thay nut nao de xoa voi gia tri: %s", x_ma);
		return;
	}
	deleteNode(root, delete_pt);

}
//=============================END-DELETION=============================