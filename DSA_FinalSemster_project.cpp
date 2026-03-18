#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <cctype> //character based functions
#include <limits> //handling

using namespace std;

// ---------------------- Data types for array-based system ----------------------
struct Customer {
    int id;
    string name;
    double balance;
};

// ---------------------- Linked-list node (separate type to avoid conflict) ----------------------
struct LLNode {
    int id;
    string name;
    double balance;
    LLNode* next;
    LLNode(int _id=0, string _name="", double _bal=0.0) : id(_id), name(_name), balance(_bal), next(nullptr) {}
};

// ---------------------- Console color helpers ----------------------
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(int color) { SetConsoleTextAttribute(hConsole, color); }

// Pause helper
void pauseAndWait() {
    setColor(8);
    cout << "\nPress any key to continue...";
    setColor(7);
    system("pause > nul");
}

// Center text inside width
string centerText(const string &s, int width) {
    if ((int)s.length() >= width) return s.substr(0, width);
    int left = (width - (int)s.length()) / 2;
    string res(left, ' ');
    res += s;
    return res;
}

// Title box
void drawTitleBox(const string &title) {
    const int width = 70;
    setColor(14); // Yellow
    cout << "+" << string(width - 2, '=') << "+" << endl;
    setColor(11); // Cyan
    cout << "| " << centerText(title, width - 4) << " |" << endl;
    setColor(14);
    cout << "+" << string(width - 2, '=') << "+" << endl;
    setColor(7);
}

// Separator
void sepLine() {
    setColor(8);
    cout << "-------------------------------------------------------------------" << endl;
    setColor(7);
}

// tolower helper
string toLowerStr(const string &s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), [](unsigned char c){ return tolower(c); });
    return out;
}

// ---------------------- ALGORITHM MODE (menus + bank-specific algorithms) ----------------------

void showArrayInsertionAlgorithm(int choice) {
    setColor(11);
    drawTitleBox("ARRAY - INSERTION ALGORITHM (Bank Context)");
    setColor(10);
    if (choice == 1) 
	{
        cout << "\nInsert at Start (Bank):\n\n";
        cout << "1. Validate new customer's ID is unique (linear scan of array by ID).\n";
        cout << "2. If current size == capacity -> resize dynamic array (allocate new larger array, copy, free old).\n";
        cout << "3. Shift all existing customers right by one index from last to index 0.\n";
        cout << "   - for i from size-1 down to 0: arr[i+1] = arr[i]\n";
        cout << "4. Place new customer record at index 0: arr[0] = {ID, Name, Balance}.\n";
        cout << "5. size = size + 1.\n";
        cout << "6. Maintain transaction log (optional), and mark sorted flag = false.\n";
    }
	 else if (choice == 2) 
	{
        cout << "\nInsert at End (Bank):\n\n";
        cout << "1. Validate ID uniqueness (linear scan).\n";
        cout << "2. If size == capacity -> resize dynamic array.\n";
        cout << "3. Place new record at arr[size].\n";
        cout << "4. size = size + 1.\n";
        cout << "5. For sorted-by-id invariant: if newID >= lastID then sorted remains true else set sorted=false.\n";
    }
	 else if (choice == 3) 
	{
        cout << "\nInsert at Specific Position (Bank):\n\n";
        cout << "1. Validate position in [0..size].\n";
        cout << "2. Validate ID uniqueness.\n";
        cout << "3. If size == capacity -> resize dynamic array.\n";
        cout << "4. Shift elements from pos..size-1 one step right (for i=size-1 down to pos: arr[i+1]=arr[i]).\n";
        cout << "5. Place new record at arr[pos].\n";
        cout << "6. size++ and update sorted flag accordingly.\n";
    } 
	else 
	{
        cout << "Invalid insertion choice.\n";
    }
    setColor(7);
}

void showArraySearchingAlgorithm(int choice)
 {
    setColor(11);
    drawTitleBox("ARRAY - SEARCHING ALGORITHMS (Bank Context)");
    setColor(10);
    if (choice == 1) 
	{
        cout << "\nLinear Search (Search customer by ID) - Bank Context:\n\n";
        cout << "Goal: find customer index given Account ID (works on unsorted array).\n";
        cout << "Steps:\n";
        cout << "1. Start from i = 0.\n";
        cout << "2. While i < size:\n";
        cout << "   a) If arr[i].id == targetID -> return i (found).\n";
        cout << "   b) Else i++.\n";
        cout << "3. If loop ends -> return NOT FOUND.\n";
        cout << "Notes: Use for small arrays or when array not sorted. O(n) worst-case.\n";
    }
	 else if (choice == 2) {
        cout << "\nBinary Search (Search customer by ID) - Bank Context:\n\n";
        cout << "Precondition: array must be sorted ascending by ID and sorted flag must be true.\n";
        cout << "Steps:\n";
        cout << "1. low = 0; high = size - 1.\n";
        cout << "2. While low <= high:\n";
        cout << "   a) mid = low + (high - low) / 2.\n";
        cout << "   b) If arr[mid].id == targetID -> return mid (found).\n";
        cout << "   c) Else if arr[mid].id < targetID -> low = mid + 1.\n";
        cout << "   d) Else high = mid - 1.\n";
        cout << "3. If loop ends -> return NOT FOUND.\n";
        cout << "Notes: O(log n) for search but requires maintenance of sorted-by-id property after insert/delete.\n";
    } else {
        cout << "Invalid searching choice.\n";
    }
    setColor(7);
}
void transactionMenu() 
{
    int transactionChoice;

    cout << "======================================" << endl;
    cout << "--- Deposit / Withdraw (Transactions) ---\n\n";
    cout << "1 - Deposit to Account" << endl;
    cout << "2 - Withdraw from Account" << endl;
    cout << "\nEnter your choice: ";
    cout << "\n======================================" << endl;

    cin >> transactionChoice;
    system("cls");

    switch (transactionChoice)
	 {
        case 1:
            cout << "========== Deposit to Account ==========\n\n";
            cout << "1. Validate that the deposit amount is positive.\n";
            cout << "2. Find the account by ID using linear search.\n";
            cout << "   - If not found, show error message.\n";
            cout << "3. Add the amount to the customer's balance.\n";
            cout << "\n=============================================" << endl;
            
            break;

        case 2:
            cout << "========== Withdraw from Account ==========\n\n";
            cout << "1. Validate that the withdrawal amount is positive.\n";
            cout << "2. Find the account by ID using linear search.\n";
            cout << "3. Check if balance is less than amount:\n";
            cout << "   - If yes, reject transaction (insufficient funds).\n";
            cout << "   - If no, subtract amount and confirm success.\n";
            cout << "\n=============================================" << endl;
          
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
            cout << "=============================================" << endl;
            ;
            break;
    }
}

void sortingMenu() {
    int sortChoice;

    cout << "======================================" << endl;
    cout << "\n--- Sort Customer List (Bank Context) ---\n\n";
    cout << "1 - Sort by ID (Bubble Sort)" << endl;
    cout << "2 - Sort by Name (Lexicographic)" << endl;
    cout << "3 - Sort by Balance (Numeric)" << endl;
    cout << "Enter your choice: ";
    cout << "\n======================================" << endl;

    cin >> sortChoice;
    system("cls");

    switch (sortChoice)
	 {
        case 1:
            cout << "\n--- Bubble Sort by ID (Ascending) ---\n\n";
            cout << "1. Traverse the customer list multiple times.\n";
            cout << "2. Compare adjacent IDs.\n";
            cout << "3. Swap if the left ID is greater than the right.\n";
            cout << "4. Repeat until no swaps are needed.\n";
            cout << "\n=============================================" << endl;
          
            break;

        case 2:
            cout << "\n--- Sort by Name (Lexicographic) ---\n\n";
            cout << "1. Convert all names to lowercase for consistency.\n";
            cout << "2. Compare names alphabetically.\n";
            cout << "3. Swap if needed to maintain order.\n";
            cout << "4. Useful for alphabetical listings or reports.\n";
            cout << "\n=============================================" << endl;
           
            break;

        case 3:
            cout << "\n--- Sort by Balance (Numeric) ---\n\n";
            cout << "1. Compare customer balances.\n";
            cout << "2. Sort in ascending or descending order based on need.\n";
            cout << "3. Useful for generating reports like top depositors.\n";
            cout << "\n=============================================" << endl;
            system("pause");
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
           
            break;
    }
}
void showArraySortingAlgorithm() 
{
    setColor(11);
    drawTitleBox("ARRAY - BUBBLE SORT ALGORITHM (Bank Context)");
    setColor(10);
    sortingMenu();
    setColor(7);
}

void showArrayUpdateAlgorithm() 
{
    setColor(11);
    drawTitleBox("ARRAY - UPDATE ALGORITHM (Bank Context)");
    setColor(10);
    cout << "\nUpdate Customer Record (Name and/or Balance) - Bank Context:\n\n";
    cout << "1. Locate customer via Linear Search by ID (or Binary if sorted-by-id).\n";
    cout << "2. If not found -> return 'Account not found'.\n";
    cout << "3. Validate input fields (name non-empty; balance >= 0 if replacing balance directly).\n";
    cout << "4. Update fields in-place: arr[idx].name = newName; arr[idx].balance = newBalance.\n";
    cout << "5. Log the change (optional). If ID changed (not recommended), update sorted flag.\n";
    setColor(7);
}

void showArrayDeleteAlgorithm(int choice) 
{
    setColor(11);
    drawTitleBox("ARRAY - DELETE ALGORITHM (Bank Context)");
    setColor(10);
    if (choice == 1) {
        cout << "\nDelete at Start (Bank Context):\n\n";
        cout << "1. If size == 0 -> Underflow / no accounts to delete.\n";
        cout << "2. Optional: if arr[0].balance > 0 -> prompt for transfer/withdraw before deletion.\n";
        cout << "3. Shift elements left from i=1..size-1: arr[i-1] = arr[i].\n";
        cout << "4. size = size - 1.\n";
    } 
	else if (choice == 2) 
	{
        cout << "\nDelete at End (Bank Context):\n\n";
        cout << "1. If size == 0 -> Underflow.\n";
        cout << "2. Optional: if last account has balance > 0 handle transfer/withdraw.\n";
        cout << "3. size = size - 1 (effectively ignores last element).\n";
    } 
	else if (choice == 3) 
	{
        cout << "\nDelete at Specific Position (Bank Context):\n\n";
        cout << "1. Validate position in [0..size-1].\n";
        cout << "2. Optional: check balance before deletion and handle.\n";
        cout << "3. Shift elements left from pos+1..size-1: arr[i-1] = arr[i].\n";
        cout << "4. size--.\n";
    } 
	else if (choice == 4) 
	{
        cout << "\nDelete by Account ID (Bank Context):\n\n";
        cout << "1. Find index via Linear Search (or Binary Search if sorted-by-id).\n";
        cout << "2. If not found -> return 'account not found'.\n";
        cout << "3. If balance > 0 -> prompt to withdraw or transfer to another account.\n";
        cout << "4. Shift left from idx+1..size-1 and size--.\n";
    }
	 else
	  {
        cout << "Invalid delete choice.\n";
    }
    setColor(7);
}

void showArrayTransactionAlgorithm() {
    setColor(11);
     transactionMenu() ;
    setColor(7);
}

// ------------------- LINKED LIST (Algorithm display) implementations -------------------

void showLinkedListInsertionAlgorithm(int choice) {
    setColor(11);
    drawTitleBox("LINKED LIST - INSERTION ALGORITHM");
    setColor(10);

    if (choice == 1)
	 {
        cout << "Algorithm: Insert at Head\n";
        cout << "1. Create a new transaction record (newNode) with the given details (Transaction ID, Amount, Type, etc.)\n";
        cout << "2. Set newNode -> next = head (link the new transaction to the existing first transaction).\n";
        cout << "3. Update head = newNode (make the new transaction the first in the list).\n";
        cout << "4. If the list was empty (tail == NULL), then set tail = newNode (so both head and tail point to the same transaction).\n";
    } 
	else if (choice == 2) 
	{
        cout << "Algorithm: Insert at Tail\n";
        cout << "1. Create a new transaction record (newNode) with the given details (Transaction ID, Amount, Type, etc.).\n";
        cout << "2. Set newNode -> next = NULL (since it will be the last transaction).\n";
        cout << "3. If the list is empty (head == NULL), then set head = tail = newNode.\n";
        cout << "4. Otherwise, link the current last transaction to the new one: tail -> next = newNode.\n";
        cout << "5. Update tail = newNode (make the new transaction the last in the list).\n";
    } else if (choice == 3) 
	{
        cout << "Algorithm: Insert at Specific Position\n";
        cout << "1. Validate the position (check if it is within the valid range of the transaction list).\n";
        cout << "2. Traverse the list to reach the transaction just before the desired position (position – 1).\n";
        cout << "3. Set newNode -> next = prev -> next (link the new transaction to the next transaction in sequence).\n";
        cout << "4. Set prev -> next = newNode (insert the new transaction after the previous one).\n";
        cout << "5. If newNode -> next == NULL, update tail = newNode (the new transaction becomes the last transaction).\n";
    }
    setColor(7);
}

void showLinkedListDeletionAlgorithm(int choice) {
    setColor(11);
    drawTitleBox("LINKED LIST - DELETION ALGORITHM");
    setColor(10);

    if (choice == 1) 
	{
        cout << "Algorithm: Delete at Head\n";
        cout << "1. If head == NULL, the transaction list is empty -> no deletion possible.\n";
        cout << "2. Set temp = head (store the first transaction).\n";
        cout << "3. Update head = head -> next (move the head to the next transaction).\n";
        cout << "4. Free/Delete temp (remove the first transaction from memory).\n";
        cout << "5. If head == NULL, set tail = NULL (the list is now empty after deletion).\n";
    } 
	else if (choice == 2) 
	{
        cout << "Algorithm: Delete at Tail\n";
        cout << "1. If head == NULL, the transaction list is empty -> no deletion possible.\n";
        cout << "2. If there is only one transaction (head == tail):"; 
		cout << "a) Delete that transaction.";
		cout << "b) Set head = tail = NULL.\n";
        cout << "3. Otherwise, traverse the list to reach the second last transaction.\n";
        cout << "4. Delete the last transaction (free memory of tail).\n";
        cout << "5. Update tail = secondLast, and set tail -> next = NULL.\n";
    } 
	else if (choice == 3)
	 {
        cout << "Algorithm: Delete by Account ID\n";
        cout << "1. If head == NULL, the transaction list is empty -> no deletion possible\n";
        cout << "2. If head -> id == key, then delete the first transaction (update head, free memory, and handle tail if needed).\n";
        cout << "3. Otherwise, traverse the list until you find the transaction with the given Account ID (key).\n";
        cout << "4. Set prev -> next = target -> next (unlink the transaction from the list).\n";
        cout << "5. Free/Delete target (remove the transaction from memory).\n";
    } 
	else if (choice == 4)
	 {
    	cout << "Algorithm: Delete At Specific Position\n";
        cout << "1. If head == NULL, the transaction list is empty -> no deletion possible.\n";
        cout << "2. If position == 1:\n";
        cout << "Delete the first transaction (update head, free memory, and handle tail if needed).\n";
        cout << "3. Otherwise, traverse the list to reach the transaction just before the desired position (position – 1).\n";
        cout << "4. Set target = prev -> next (the transaction to be deleted).\n";
        cout << "5. Set prev -> next = target -> next (unlink the target transaction).\n";
        cout << "6. If target -> next == NULL, update tail = prev (deletion was at the end).\n";
        cout << "7. Free/Delete target (remove the transaction from memory).\n";
	}
    setColor(7);
}

void showLinkedListSearchingAlgorithm() {
    setColor(11);
    drawTitleBox("LINKED LIST - SEARCHING ALGORITHM");
    setColor(10);

    cout << "Algorithm: Linear Search By Account Id \n";
    cout << "1. Set current = head (start from the first record in the list).\n";
    cout << "2. While current != NULL:\n";
    cout << "a) If current -> id == target, return FOUND (the account/transaction exists).\n";
    cout << "b) Otherwise, move current = current -> next.\n";
    cout << "3. If the loop ends, return NOT FOUND (the account/transaction does not exist).\n";
    setColor(7);
}

void showLinkedListUpdateAlgorithm() 
{
    setColor(11);
    drawTitleBox("LINKED LIST - UPDATE ALGORITHM");
    setColor(10);

    cout << "Algorithm: Update Node by ID\n";
    cout << "1. Search for the account node by Account ID (using linear search).\n";
    cout << "2. If not found, display “Account not found”.\n";
    cout << "3. If found, update the details of that account:\n";
    cout << "a) node -> name (update customer’s name).";
    cout << "b) node -> balance (update account balance).";
    cout << "4. Save/Store the updated node back into the list.\n";
    setColor(7);
}

void showLinkedListSortingAlgorithm(int choice) 
{
    setColor(11);
    drawTitleBox("LINKED LIST - SORTING ALGORITHM");
    setColor(10);

    if (choice == 1){
    cout << "Algorithm: Bubble Sort by ID\n";
    cout << "1. If list empty or only one node, exit.\n";
    cout << "2. Repeat until no swaps:\n";
    cout << "   a) Set current = head.\n";
    cout << "   b) While current->next != NULL:\n";
    cout << "        If current->id > current->next->id, swap data.\n";
    cout << "        Move to next node.\n";
    cout << "3. Stop when a full pass has no swaps.\n";
	} 
	else if (choice == 2)
	{
	cout << "Algorithm: Selection Sort\n";
    cout << "1. Set current = head.\n";
    cout << "2. While current != NULL:\n";
    cout << "   a) Set minNode = current.\n";
    cout << "   b) Traverse from current->next to end:\n";
    cout << "      - If node->id < minNode->id, set minNode = node.\n";
    cout << "   c) If minNode != current, swap account details.\n";
    cout << "   d) Move current = current->next.\n\n";
	}
	 else if (choice == 3){
	cout << "Algorithm: Insertion Sort\n";
    cout << "1. Initialize sorted = NULL.\n";
    cout << "2. Set current = head.\n";
    cout << "3. While current != NULL:\n";
    cout << "   a) Save next = current->next.\n";
    cout << "   b) Insert current into correct position in sorted list.\n";
    cout << "      - If sorted == NULL OR current->id < sorted->id, insert at head.\n";
    cout << "      - Else traverse sorted and insert at proper place.\n";
    cout << "   c) Update current = next.\n";
    cout << "4. Set head = sorted.\n\n";
	} 
	else if (choice == 4){
	cout << "Algorithm: Merge Sort\n";
    cout << "1. If head == NULL OR head->next == NULL, return (already sorted).\n";
    cout << "2. Split list into two halves using slow/fast pointers.\n";
    cout << "3. Recursively apply mergeSort on both halves.\n";
    cout << "4. Merge the two sorted halves:\n";
    cout << "   - Compare nodes by ID (or balance).\n";
    cout << "   - Insert smaller node first.\n";
    cout << "   - Continue until all nodes are merged.\n";
    cout << "5. Update head with merged list.\n";
	}
    setColor(7);
}

void showLinkedListTransactionAlgorithm() {
    setColor(11);
    drawTitleBox("LINKED LIST - TRANSACTION ALGORITHM");
    setColor(10);

    cout << "Algorithm: Deposit\n";
    cout << "1. Search for the account by Account ID (traverse the linked list).\n";
    cout << "2. If not found, display “Account not found\n";
    cout << "3. If found, update the account balance:\n";
    cout << "a) balance = balance + amount";
    cout << "4. Save the updated account record.\n";         
                
    cout << "Algorithm: Withdraw\n";
    cout << "1. Search for the account by Account ID (traverse the linked list)\n";
    cout << "2. If not found, display “Account not found”.\n";
    cout << "3. If found, check if balance >= amount.\n";
    cout << "4. If valid, update the account balance:\n";
	cout << "a) balance = balance - amount";
    cout << "5. Else, display “Insufficient funds”.\n";
    cout << "6. Save the updated account record.\n";
    setColor(7);
}
// ==========================
// DOUBLY LINKED LIST (DLL) ALGORITHMS
// ==========================

void showDoublyLinkedListInsertionAlgorithm(int choice) {
    setColor(11);
    drawTitleBox("DOUBLY LINKED LIST (DLL) - INSERTION ALGORITHMS");
    setColor(10);

    if (choice == 1) {
        cout << "Algorithm 1: Insert Account at Head\n";
        cout << "1. Create newAccount node.\n";
        cout << "2. Set newAccount->next = head.\n";
        cout << "3. Set newAccount->prev = NULL.\n";
        cout << "4. If head != NULL then set head->prev = newAccount.\n";
        cout << "5. Update head = newAccount.\n";
    }
    else if (choice == 2) {
        cout << "Algorithm 2: Insert Account at Tail\n";
        cout << "1. Create newAccount node.\n";
        cout << "2. If head == NULL then set head = newAccount.\n";
        cout << "3. Else traverse to the last node using temp = head.\n";
        cout << "4. While temp->next != NULL, move temp = temp->next.\n";
        cout << "5. Set temp->next = newAccount.\n";
        cout << "6. Set newAccount->prev = temp.\n";
    }
    else if (choice == 3) {
        cout << "Algorithm 3: Insert Account at Specific Position\n";
        cout << "1. Traverse to (position - 1)th account.\n";
        cout << "2. Set newAccount->next = current->next.\n";
        cout << "3. Set newAccount->prev = current.\n";
        cout << "4. If current->next != NULL then set current->next->prev = newAccount.\n";
        cout << "5. Set current->next = newAccount.\n";
    }
    setColor(7);
}

void showDoublyLinkedListDeletionAlgorithm(int choice) {
    setColor(11);
    drawTitleBox("DOUBLY LINKED LIST (DLL) - DELETION ALGORITHMS");
    setColor(10);

    if (choice == 1) {
        cout << "Algorithm 4: Delete Account at Head\n";
        cout << "1. If head == NULL → return (list empty).\n";
        cout << "2. Set temp = head.\n";
        cout << "3. Update head = head->next.\n";
        cout << "4. If head != NULL then head->prev = NULL.\n";
        cout << "5. Delete temp.\n";
    }
    else if (choice == 2) {
        cout << "Algorithm 5: Delete Account at Tail\n";
        cout << "1. If head == NULL → return (list empty).\n";
        cout << "2. Set temp = head.\n";
        cout << "3. While temp->next != NULL move temp = temp->next.\n";
        cout << "4. temp->prev->next = NULL.\n";
        cout << "5. Delete temp.\n";
    }
    else if (choice == 3) {
        cout << "Algorithm 6: Delete Account by Account ID\n";
        cout << "1. Set temp = head.\n";
        cout << "2. Traverse until temp == NULL or temp->accountID == targetID.\n";
        cout << "3. If temp == NULL, print 'Account not found'.\n";
        cout << "4. Else:\n";
        cout << "   a) If temp->prev != NULL then temp->prev->next = temp->next.\n";
        cout << "   b) If temp->next != NULL then temp->next->prev = temp->prev.\n";
        cout << "   c) If temp == head then head = temp->next.\n";
        cout << "   d) Delete temp.\n";
    }
    setColor(7);
}

void showDoublyLinkedListSearchAlgorithm() {
    setColor(11);
    drawTitleBox("DOUBLY LINKED LIST (DLL) - SEARCH ALGORITHM");
    setColor(10);

    cout << "Algorithm 7: Search Account by ID\n";
    cout << "1. Set temp = head.\n";
    cout << "2. While temp != NULL:\n";
    cout << "   a) If temp->accountID == targetID → return temp.\n";
    cout << "   b) Move temp = temp->next.\n";
    cout << "3. Return NULL (account not found).\n";
    setColor(7);
}

void showDoublyLinkedListUpdateAlgorithm() {
    setColor(11);
    drawTitleBox("DOUBLY LINKED LIST (DLL) - UPDATE ALGORITHM");
    setColor(10);

    cout << "Algorithm 8: Update Account Information\n";
    cout << "1. account = Search(targetID).\n";
    cout << "2. If account != NULL then:\n";
    cout << "   a) Update account->name or account->balance as required.\n";
    cout << "3. Else print 'Account not found'.\n";
    setColor(7);
}

void showDoublyLinkedListSortingAlgorithm(int choice) {
    setColor(11);
    drawTitleBox("DOUBLY LINKED LIST (DLL) - SORTING ALGORITHMS");
    setColor(10);

    if (choice == 1) {
        cout << "Algorithm 9: Sort Accounts by ID (Selection Sort)\n";
        cout << "1. Set current = head.\n";
        cout << "2. While current != NULL:\n";
        cout << "   a) Set index = current->next.\n";
        cout << "   b) While index != NULL:\n";
        cout << "      - If current->accountID > index->accountID, swap their data.\n";
        cout << "      - Move index = index->next.\n";
        cout << "   c) Move current = current->next.\n";
    }
    else if (choice == 2) {
        cout << "Algorithm 10: Bubble Sort (by Balance)\n";
        cout << "1. Start from head of list.\n";
        cout << "2. Initialize swapped = false.\n";
        cout << "3. While traversing list:\n";
        cout << "   a) Compare each node’s balance with next node’s balance.\n";
        cout << "   b) If current->balance > next->balance, swap all data fields.\n";
        cout << "   c) Set swapped = true.\n";
        cout << "4. Repeat until no swaps occur (list sorted).\n";
    }
    else if (choice == 3) {
        cout << "Algorithm 11: Insertion Sort (by Balance)\n";
        cout << "1. Initialize an empty list called sortedList.\n";
        cout << "2. Take each node from original list one by one.\n";
        cout << "3. For each node:\n";
        cout << "   a) Find the correct position in sortedList based on balance.\n";
        cout << "   b) Insert it (update prev and next links).\n";
        cout << "4. After all nodes processed, head = sortedList.\n";
    }
    else if (choice == 4) {
        cout << "Algorithm 12: Merge Sort (by Balance)\n";
        cout << "1. Divide Step:\n";
        cout << "   a) Split the list into two halves using slow–fast pointers.\n";
        cout << "2. Recursive Step:\n";
        cout << "   a) Recursively apply merge sort to both halves.\n";
        cout << "3. Merge Step:\n";
        cout << "   a) Merge the two sorted halves comparing balances.\n";
        cout << "   b) Adjust prev and next links properly.\n";
        cout << "4. Continue merging until the entire list is sorted.\n";
    }
    setColor(7);
}

void showDoublyLinkedListTransactionAlgorithm() {
    setColor(11);
    drawTitleBox("DOUBLY LINKED LIST (DLL) - TRANSACTION ALGORITHM");
    setColor(10);

    cout << "Algorithm 13: Deposit and Withdraw\n\n";
    cout << "Deposit:\n";
    cout << "1. account = Search(targetID).\n";
    cout << "2. If account != NULL then account->balance += amount.\n";
    cout << "3. Else print 'Account not found'.\n\n";

    cout << "Withdraw:\n";
    cout << "1. account = Search(targetID).\n";
    cout << "2. If account != NULL and account->balance >= amount:\n";
    cout << "   a) account->balance -= amount.\n";
    cout << "3. Else print 'Insufficient balance'.\n";
    setColor(7);
}
// ==========================
// CIRCULAR SINGLY LINKED LIST (CSLL) ALGORITHMS
// ==========================

void showCircularSinglyLinkedListAlgorithms() {
    int choice;
    do {
        system("cls");
        drawTitleBox("CIRCULAR SINGLY LINKED LIST (CSLL) - ALGORITHMS");
        setColor(10);
        cout << "\n1. Insert at Head";
        cout << "\n2. Insert at Tail";
        cout << "\n3. Insert at Specific Position";
        cout << "\n4. Delete at Head";
        cout << "\n5. Delete at Tail";
        cout << "\n6. Search Account by ID";
        cout << "\n7. Update Account";
        cout << "\n8. Bubble Sort";
        cout << "\n9. Insertion Sort";
        cout << "\n10. Merge Sort";
        cout << "\n11. Selection Sort";
        cout << "\n12. Deposit Amount";
        cout << "\n13. Withdraw Amount";
        cout << "\n0. Back";
        setColor(7);
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                drawTitleBox("Insert Account at Head (CSLL)");
                cout << "1. Create newAccount node.\n";
                cout << "2. If head == NULL: head = newAccount; newAccount->next = head.\n";
                cout << "3. Else traverse to last node and link newAccount at head.\n";
                break;

            case 2:
                drawTitleBox("Insert Account at Tail (CSLL)");
                cout << "1. Create newAccount node.\n";
                cout << "2. If head == NULL: head = newAccount; newAccount->next = head.\n";
                cout << "3. Else traverse to last node and link newAccount at tail.\n";
                break;

            case 3:
                drawTitleBox("Insert Account at Specific Position (CSLL)");
                cout << "Algorithm InsertAtPosition(head, newAccount, position):\n";
                cout << "1. Create new node.\n2. If head == NULL -> make it circular.\n";
                cout << "3. If position == 1 -> insert at head.\n";
                cout << "4. Else traverse to (position-1) node and insert.\n";
                break;

            case 4:
                drawTitleBox("Delete at Head (CSLL)");
                cout << "1. If head == NULL -> list empty.\n";
                cout << "2. If head->next == head -> delete head.\n";
                cout << "3. Else traverse last node, update links, delete old head.\n";
                break;

            case 5:
                drawTitleBox("Delete at Tail (CSLL)");
                cout << "1. If head == NULL -> list empty.\n";
                cout << "2. If head->next == head -> delete head.\n";
                cout << "3. Else traverse second-last node, delete tail, update links.\n";
                break;

            case 6:
                drawTitleBox("Search Account by ID (CSLL)");
                cout << "1. Traverse from head circularly.\n";
                cout << "2. Compare accountID, return node if found.\n";
                break;

            case 7:
                drawTitleBox("Update Account (CSLL)");
                cout << "1. Search account by ID.\n";
                cout << "2. If found, update name or balance.\n";
                cout << "3. Else show 'Account not found'.\n";
                break;

            case 8:
                drawTitleBox("Bubble Sort (CSLL)");
                cout << "Compare each node's balance circularly, swap if needed until sorted.\n";
                break;

            case 9:
                drawTitleBox("Insertion Sort (CSLL)");
                cout << "Traverse nodes and insert in sorted circular list maintaining order.\n";
                break;

            case 10:
                drawTitleBox("Merge Sort (CSLL)");
                cout << "Split circular list, recursively sort halves, merge maintaining circularity.\n";
                break;

            case 11:
                drawTitleBox("Selection Sort (CSLL)");
                cout << "Find min node in circular traversal, swap data, repeat until sorted.\n";
                break;

            case 12:
                drawTitleBox("Deposit Amount (CSLL)");
                cout << "Find account by ID, increase balance if found.\n";
                break;

            case 13:
                drawTitleBox("Withdraw Amount (CSLL)");
                cout << "Find account by ID, decrease balance if sufficient funds.\n";
                break;

            case 0:
                setColor(11);
                cout << "Returning to Circular Linked List Menu...\n";
                setColor(7);
                break;

            default:
                setColor(12);
                cout << "Invalid choice! Try again.\n";
                setColor(7);
        }

        if (choice != 0) pauseAndWait();

    } while (choice != 0);
}

// ==========================
// CIRCULAR DOUBLY LINKED LIST (CDLL) ALGORITHMS
// ==========================

void showCircularDoublyLinkedListAlgorithms() {
    int choice;
    do {
        system("cls");
        drawTitleBox("CIRCULAR DOUBLY LINKED LIST (CDLL) - ALGORITHMS");
        setColor(10);
        cout << "\n1. Insert at Head";
        cout << "\n2. Insert at Tail";
        cout << "\n3. Insert at Specific Position";
        cout << "\n4. Delete by ID";
        cout << "\n5. Delete at Head";
        cout << "\n6. Delete at Tail";
        cout << "\n7. Search Account by ID";
        cout << "\n8. Update Account";
        cout << "\n9. Bubble Sort";
        cout << "\n10. Insertion Sort";
        cout << "\n11. Selection Sort";
        cout << "\n12. Merge Sort";
        cout << "\n13. Deposit Amount";
        cout << "\n14. Withdraw Amount";
        cout << "\n0. Back";
        setColor(7);
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                drawTitleBox("Insert at Head (CDLL)");
                cout << "Create new node, adjust head, prev, next pointers.\n";
                break;
            case 2:
                drawTitleBox("Insert at Tail (CDLL)");
                cout << "Create new node, adjust tail links before head.\n";
                break;
            case 3:
                drawTitleBox("Insert at Specific Position (CDLL)");
                cout << "Traverse to position, insert node, fix next and prev pointers.\n";
                break;
            case 4:
                drawTitleBox("Delete by ID (CDLL)");
                cout << "Traverse circularly, unlink node with target ID, delete node.\n";
                break;
            case 5:
                drawTitleBox("Delete at Head (CDLL)");
                cout << "Adjust head and tail pointers, delete old head.\n";
                break;
            case 6:
                drawTitleBox("Delete at Tail (CDLL)");
                cout << "Adjust tail and previous node pointers, delete last node.\n";
                break;
            case 7:
                drawTitleBox("Search Account (CDLL)");
                cout << "Traverse circularly, print account details if found.\n";
                break;
            case 8:
                drawTitleBox("Update Account (CDLL)");
                cout << "Traverse circularly, update name/balance if account found.\n";
                break;
            case 9:
                drawTitleBox("Bubble Sort (CDLL)");
                cout << "Compare adjacent balances circularly, swap until sorted.\n";
                break;
            case 10:
                drawTitleBox("Insertion Sort (CDLL)");
                cout << "Build sorted CDLL from original list by inserting each node in order.\n";
                break;
            case 11:
                drawTitleBox("Selection Sort (CDLL)");
                cout << "Find min node in circular traversal, swap data, repeat until sorted.\n";
                break;
            case 12:
                drawTitleBox("Merge Sort (CDLL)");
                cout << "Split circular list, recursively sort halves, merge maintaining circularity.\n";
                break;
            case 13:
                drawTitleBox("Deposit Amount (CDLL)");
                cout << "Find account, add amount to balance.\n";
                break;
            case 14:
                drawTitleBox("Withdraw Amount (CDLL)");
                cout << "Find account, subtract amount if sufficient balance.\n";
                break;
            case 0:
                setColor(11);
                cout << "Returning to Circular Linked List Menu...\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "Invalid choice! Try again.\n";
                setColor(7);
        }

        if (choice != 0) pauseAndWait();

    } while (choice != 0);
}



// Algorithm mode top-level
void algorithmMode() {
    while (true) {
        system("cls");
        drawTitleBox("ALGORITHM MODE - CHOOSE DATA STRUCTURE");
        setColor(10);
        cout << "\nSelect a Data Structure (or 0 to return):\n\n";
        cout << "1. Array \n";
        cout << "2. Linked List\n";
        cout << "3. Stack\n";
        cout << "4. Queue\n";
        cout << "0. Return to Welcome Page\n";
        setColor(7);
        cout << "\nEnter your choice: ";
        int dsChoice;
        cin >> dsChoice;

        if (dsChoice == 0) return;

        if (dsChoice == 1) { // ARRAY
            while (true) {
                system("cls");
                drawTitleBox("ARRAY - OPERATIONS (Algorithm Mode)");
                setColor(10);
                cout << "\nChoose operation (0 to go back):\n\n";
                cout << "1. Insertion\n";
                cout << "2. Searching\n";
                cout << "3. Sorting\n";
                cout << "4. Update\n";
                cout << "5. Delete\n";
                cout << "6. Deposit / Withdraw\n";
                cout << "0. Back to Data Structure Menu\n";
                setColor(7);
                cout << "\nEnter your choice: ";
                int arrChoice;
                cin >> arrChoice;
                if (arrChoice == 0) break;

                if (arrChoice == 1) {
                    system("cls");
                    drawTitleBox("ARRAY - INSERTION (Choose Type)");
                    setColor(10);
                    cout << "\nWhere do you want to insert?\n";
                    cout << "1. At Start\n";
                    cout << "2. At End\n";
                    cout << "3. At Specific Position\n";
                    cout << "0. Back\n";
                    setColor(7);
                    cout << "Choice: ";
                    int insChoice; cin >> insChoice;
                    showArrayInsertionAlgorithm(insChoice);
                    pauseAndWait();
                } else if (arrChoice == 2) {
                    system("cls");
                    drawTitleBox("ARRAY - SEARCHING (Choose Type)");
                    setColor(10);
                    cout << "\nSearching methods:\n";
                    cout << "1. Linear Search\n";
                    cout << "2. Binary Search\n";
                    cout << "0. Back\n";
                    setColor(7);
                    cout << "Choice: ";
                    int sChoice; cin >> sChoice;
                    showArraySearchingAlgorithm(sChoice);
                    pauseAndWait();
                } else if (arrChoice == 3) {
                    system("cls");
                    showArraySortingAlgorithm();
                    pauseAndWait();
                } else if (arrChoice == 4) {
                    system("cls");
                    showArrayUpdateAlgorithm();
                    pauseAndWait();
                } else if (arrChoice == 5) {
                    system("cls");
                    drawTitleBox("ARRAY - DELETE (Choose Type)");
                    setColor(10);
                    cout << "\nDelete options:\n";
                    cout << "1. At Start\n";
                    cout << "2. At End\n";
                    cout << "3. At Specific Position\n";
                    cout << "4. By Account ID\n";
                    cout << "0. Back\n";
                    setColor(7);
                    cout << "Choice: ";
                    int dChoice; cin >> dChoice;
                    showArrayDeleteAlgorithm(dChoice);
                    pauseAndWait();
                } else if (arrChoice == 6) {
                    system("cls");
                    showArrayTransactionAlgorithm();
                    pauseAndWait();
                } else {
                    setColor(12);
                    cout << "Invalid choice.\n";
                    setColor(7);
                    pauseAndWait();
                }
            }
        } else if (dsChoice == 2) { // LINKED LIST
    system("cls");
    drawTitleBox("LINKED LIST - ALGORITHMS");
    setColor(10);

    int listTypeChoice; // 1 = SLL, 2 = DLL, 3 = CLL

    do {
        system("cls");
        drawTitleBox("LINKED LIST TYPES");
        setColor(10);
        cout << "\n1. Singly Linked List (SLL)";
        cout << "\n2. Doubly Linked List (DLL)";
        cout << "\n3. Circular Linked List (CLL)";
        cout << "\n0. Back";
        setColor(7);
        cout << "\n\nEnter your choice: ";
        cin >> listTypeChoice;

        // ========== SINGLY LINKED LIST ==========
        if (listTypeChoice == 1) {
            int sllChoice;
            do {
                system("cls");
                drawTitleBox("SINGLY LINKED LIST - MENU");
                setColor(10);
                cout << "\n1. Insertion Algorithms";
                cout << "\n2. Deletion Algorithms";
                cout << "\n3. Searching Algorithm";
                cout << "\n4. Update Algorithm";
                cout << "\n5. Sorting Algorithms";
                cout << "\n6. Transaction Algorithms";
                cout << "\n0. Back";
                setColor(7);
                cout << "\n\nEnter your choice: ";
                cin >> sllChoice;
                system("cls");

                switch (sllChoice) {
                    case 1: {
                        int choice;
                        cout << "1. Insert at Head\n2. Insert at Tail\n3. Insert at Position\nEnter choice: ";
                        cin >> choice;
                        showLinkedListInsertionAlgorithm(choice);
                        break;
                    }
                    case 2: {
                        int choice;
                        cout << "1. Delete at Head\n2. Delete at Tail\n3. Delete by ID\n4. Delete at Position\nEnter choice: ";
                        cin >> choice;
                        showLinkedListDeletionAlgorithm(choice);
                        break;
                    }
                    case 3:
                        showLinkedListSearchingAlgorithm();
                        break;
                    case 4:
                        showLinkedListUpdateAlgorithm();
                        break;
                    case 5: {
                        int choice;
                        cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\nEnter choice: ";
                        cin >> choice;
                        showLinkedListSortingAlgorithm(choice);
                        break;
                    }
                    case 6:
                        showLinkedListTransactionAlgorithm();
                        break;
                    case 0:
                        setColor(11);
                        cout << "Returning to Linked List Types...\n";
                        setColor(7);
                        break;
                    default:
                        setColor(12);
                        cout << "Invalid choice! Try again.\n";
                        setColor(7);
                }
                if (sllChoice != 0) pauseAndWait();
            } while (sllChoice != 0);
        }

        // ========== DOUBLY LINKED LIST ==========
        else if (listTypeChoice == 2) {
            int dllChoice;
            do {
                system("cls");
                drawTitleBox("DOUBLY LINKED LIST - MENU");
                setColor(10);
                cout << "\n1. Insertion Algorithms";
                cout << "\n2. Deletion Algorithms";
                cout << "\n3. Searching Algorithm";
                cout << "\n4. Update Algorithm";
                cout << "\n5. Sorting Algorithms";
                cout << "\n6. Transaction Algorithms";
                cout << "\n0. Back";
                setColor(7);
                cout << "\n\nEnter your choice: ";
                cin >> dllChoice;
                system("cls");

                switch (dllChoice) {
                    case 1: {
                        int choice;
                        cout << "1. Insert at Head\n2. Insert at Tail\n3. Insert at Position\nEnter choice: ";
                        cin >> choice;
                        showDoublyLinkedListInsertionAlgorithm(choice);
                        break;
                    }
                    case 2: {
                        int choice;
                        cout << "1. Delete at Head\n2. Delete at Tail\n3. Delete by ID\nEnter choice: ";
                        cin >> choice;
                        showDoublyLinkedListDeletionAlgorithm(choice);
                        break;
                    }
                    case 3:
                        showDoublyLinkedListSearchAlgorithm();
                        break;
                    case 4:
                        showDoublyLinkedListUpdateAlgorithm();
                        break;
                    case 5: {
                        int choice;
                        cout << "1. Selection Sort by ID\n2. Bubble Sort by Balance\n3. Insertion Sort by Balance\n4. Merge Sort by Balance\nEnter choice: ";
                        cin >> choice;
                        showDoublyLinkedListSortingAlgorithm(choice);
                        break;
                    }
                    case 6:
                        showDoublyLinkedListTransactionAlgorithm();
                        break;
                    case 0:
                        setColor(11);
                        cout << "Returning to Linked List Types...\n";
                        setColor(7);
                        break;
                    default:
                        setColor(12);
                        cout << "Invalid choice! Try again.\n";
                        setColor(7);
                }

                if (dllChoice != 0) pauseAndWait();
            } while (dllChoice != 0);
        }

        // ========== CIRCULAR LINKED LIST ==========
        else if (listTypeChoice == 3) {
            int cllChoice;
            do {
                system("cls");
                drawTitleBox("CIRCULAR LINKED LIST - MENU");
                setColor(10);
                cout << "\n1. Circular Singly Linked List (CSLL)";
                cout << "\n2. Circular Doubly Linked List (CDLL)";
                
                cout << "\n0. Back";
                setColor(7);
                cout << "\n\nEnter your choice: ";
                cin >> cllChoice;
                system("cls");

                switch (cllChoice) {
                    case 1:
                      showCircularSinglyLinkedListAlgorithms();  // your CSLL menu function
                        break;
                    case 2:
                       showCircularDoublyLinkedListAlgorithms() ;  // your CDLL menu function
                        break;
                    case 0:
                        setColor(11);
                        cout << "Returning to Linked List Types...\n";
                        setColor(7);
                        break;
                    default:
                        setColor(12);
                        cout << "Invalid choice! Try again.\n";
                        setColor(7);
                }

                if (cllChoice != 0) pauseAndWait();
            } while (cllChoice != 0);
        }

        // ========== BACK ==========
        else if (listTypeChoice == 0) {
            setColor(11);
            cout << "Returning to Algorithm Menu...\n";
            setColor(7);
        }

        else {
            setColor(12);
            cout << "Invalid choice! Try again.\n";
            setColor(7);
            pauseAndWait();
        }

    } while (listTypeChoice != 0);

    setColor(7);
    pauseAndWait();
}

//-----------------------------------------Stack--------------------------------------

        else if (dsChoice == 3) {
            system("cls");
            drawTitleBox("STACK - ALGORITHMS (Bank Context)");
            setColor(10);
            
    int stackChoice;
    do {
        system("cls");
        drawTitleBox("STACK - TRANSACTION HISTORY (Algorithm View)");
        setColor(10);
        cout << "\n1. Deposit (Push Operation)";
        cout << "\n2. Withdraw (Pop Operation)";
        cout << "\n3. View Last Transaction (Peek Operation)";
        cout << "\n4. Check if Stack is Empty";
        cout << "\n5. Check if Stack is Full";
        cout << "\n6. Circular Stack Explanation";
        cout << "\n0. Back";
        setColor(7);
        cout << "\n\nEnter your choice: ";
        cin >> stackChoice;
        system("cls");

        switch (stackChoice) {
            case 1:
                drawTitleBox("Deposit (Push Operation)");
                cout << "Purpose: To add a new transaction to the customer’s transaction history.\n\n";
                cout << "Steps:\n";
                cout << "1. Check if the customer’s transaction stack is full.\n";
                cout << "2. If it is full, display a message that no more transactions can be stored.\n";
                cout << "3. If it is not full, move the stack pointer (Top) to the next position.\n";
                cout << "4. Store the new transaction in that position.\n";
                cout << "5. Display a message that the deposit transaction has been recorded.\n";
                break;

            case 2:
                drawTitleBox("Withdraw (Pop Operation)");
                cout << "Purpose: To remove the most recent transaction from the customer’s history.\n\n";
                cout << "Steps:\n";
                cout << "1. Check if the customer’s transaction stack is empty.\n";
                cout << "2. If it is empty, display a message that there are no transactions to remove.\n";
                cout << "3. If it is not empty, take out the transaction present at the top of the stack.\n";
                cout << "4. Move the stack pointer (Top) one position back.\n";
                cout << "5. Display a message that the last transaction has been removed.\n";
                break;

            case 3:
                drawTitleBox("View Last Transaction (Peek Operation)");
                cout << "Purpose: To see the most recent transaction without removing it.\n\n";
                cout << "Steps:\n";
                cout << "1. Check if the transaction stack is empty.\n";
                cout << "2. If it is empty, display a message that no transaction exists.\n";
                cout << "3. If not empty, display the transaction currently at the top of the stack.\n";
                break;

            case 4:
                drawTitleBox("Check if Stack is Empty");
                cout << "Steps:\n";
                cout << "1. If the Top pointer is at -1, then the stack is empty.\n";
                cout << "2. Otherwise, the stack is not empty.\n";
                break;

            case 5:
                drawTitleBox("Check if Stack is Full");
                cout << "Steps:\n";
                cout << "1. If Top is at the maximum allowed index, then the stack is full.\n";
                cout << "2. Otherwise, the stack is not full.\n";
                break;

            case 6:
                drawTitleBox("Circular Stack Explanation");
                cout << "A circular stack allows the transaction history to overwrite\n";
                cout << "the oldest transaction when the limit is reached, instead of stopping when full.\n\n";
                cout << "Example in Bank Context:\n";
                cout << "If a customer’s transaction history can store only 10 transactions,\n";
                cout << "then when the 11th transaction happens, it will replace the oldest one automatically,\n";
                cout << "keeping only the most recent 10 transactions in a circular manner.\n";
                break;

            case 0:
                setColor(11);
                cout << "Returning to Algorithm Menu...\n";
                setColor(7);
                break;

            default:
                setColor(12);
                cout << "Invalid choice! Try again.\n";
                setColor(7);
        }

        if (stackChoice != 0) pauseAndWait();
    } while (stackChoice != 0);
            setColor(7);
            pauseAndWait();
        } else if (dsChoice == 4) 
		{
            system("cls");
            drawTitleBox("QUEUE - ALGORITHMS (Bank Context)");
            setColor(10);
    int queueTypeChoice;
    do {
        system("cls");
        drawTitleBox("QUEUE ALGORITHMS - BANK WAITING LINE");
        setColor(10);
        cout << "\n1. Simple Queue Algorithms";
        cout << "\n2. Circular Queue Algorithms";
        cout << "\n0. Back";
        setColor(7);
        cout << "\n\nEnter your choice: ";
        cin >> queueTypeChoice;

        if (queueTypeChoice == 1) {
            // SIMPLE QUEUE
            int queueChoice;
            do {
                system("cls");
                drawTitleBox("SIMPLE QUEUE - BANK WAITING LINE (Algorithm View)");
                setColor(10);
                cout << "\n1. Enqueue (Add Customer to Queue)";
                cout << "\n2. Dequeue (Serve Customer)";
                cout << "\n3. Front / Peek (See Who is Next)";
                cout << "\n4. isEmpty";
                cout << "\n5. isFull";
                cout << "\n0. Back";
                setColor(7);
                cout << "\n\nEnter your choice: ";
                cin >> queueChoice;
                system("cls");

                switch (queueChoice) {
                    case 1:
                        drawTitleBox("Enqueue (Add Customer to Queue)");
                        cout << "Purpose: When a new customer arrives at the bank, they join the end of the waiting line.\n\n";
                        cout << "Steps:\n";
                        cout << "1. Check if the queue is full.\n";
                        cout << "2. If it is full, display that no more customers can wait.\n";
                        cout << "3. If not full, move the rear pointer to the next position.\n";
                        cout << "4. Add the new customer at the rear position.\n";
                        cout << "5. Display that the customer has joined the queue.\n";
                        break;

                    case 2:
                        drawTitleBox("Dequeue (Serve Customer)");
                        cout << "Purpose: When a customer is served, they leave from the front of the queue.\n\n";
                        cout << "Steps:\n";
                        cout << "1. Check if the queue is empty.\n";
                        cout << "2. If it is empty, display that there are no customers to serve.\n";
                        cout << "3. If not empty, take the customer at the front.\n";
                        cout << "4. Move the front pointer to the next position.\n";
                        cout << "5. Display that the customer has been served and removed from the queue.\n";
                        break;

                    case 3:
                        drawTitleBox("Front / Peek (See Who is Next)");
                        cout << "Purpose: To view which customer will be served next without removing them.\n\n";
                        cout << "Steps:\n";
                        cout << "1. Check if the queue is empty.\n";
                        cout << "2. If empty, display that no customer is waiting.\n";
                        cout << "3. If not empty, display the customer at the front of the queue.\n";
                        break;

                    case 4:
                        drawTitleBox("isEmpty (Check Queue Empty)");
                        cout << "Purpose: To check whether the queue has any waiting customers.\n\n";
                        cout << "Steps:\n";
                        cout << "1. If front and rear indicate no entries, return true (queue is empty).\n";
                        cout << "2. Otherwise, return false.\n";
                        break;

                    case 5:
                        drawTitleBox("isFull (Check Queue Full)");
                        cout << "Purpose: To check whether the waiting area has reached full capacity.\n\n";
                        cout << "Steps:\n";
                        cout << "1. If the rear pointer is at the maximum allowed position, return true (queue is full).\n";
                        cout << "2. Otherwise, return false.\n";
                        break;

                    case 0:
                        setColor(11);
                        cout << "Returning to Queue Type Menu...\n";
                        setColor(7);
                        break;

                    default:
                        setColor(12);
                        cout << "Invalid choice! Try again.\n";
                        setColor(7);
                }

                if (queueChoice != 0) pauseAndWait();
            } while (queueChoice != 0);
        }

        else if (queueTypeChoice == 2) {
            // ----------------------------CIRCULAR QUEUE-----------------------------
            int queueChoice;
            do {
                system("cls");
                drawTitleBox("CIRCULAR QUEUE - BANK WAITING LINE (Algorithm View)");
                setColor(10);
                cout << "\n1. Enqueue (Add Customer to Circular Queue)";
                cout << "\n2. Dequeue (Serve Customer from Circular Queue)";
                cout << "\n3. Peek / Front (See Next Customer)";
                cout << "\n4. isEmpty";
                cout << "\n5. isFull";
                cout << "\n0. Back";
                setColor(7);
                cout << "\n\nEnter your choice: ";
                cin >> queueChoice;
                system("cls");

                switch (queueChoice) {
                    case 1:
                        drawTitleBox("Enqueue (Add Customer to Circular Queue)");
                        cout << "Purpose: A new customer arrives to wait for service.\n\n";
                        cout << "Steps:\n";
                        cout << "1. Check if the circular queue is full (i.e., the next position of rear is front).\n";
                        cout << "2. If full, display that no more customers can join.\n";
                        cout << "3. If not full:\n";
                        cout << "   o Move rear to the next circular position.\n";
                        cout << "   o Insert the customer at rear.\n";
                        cout << "4. Display that the customer has joined the queue.\n";
                        break;

                    case 2:
                        drawTitleBox("Dequeue (Serve Customer from Circular Queue)");
                        cout << "Purpose: The next customer is served and leaves the line.\n\n";
                        cout << "Steps:\n";
                        cout << "1. Check if the circular queue is empty (front = -1).\n";
                        cout << "2. If empty, display there are no customers to serve.\n";
                        cout << "3. If not empty:\n";
                        cout << "   o Remove the customer at front.\n";
                        cout << "   o If this was the only customer (front = rear), reset both to -1.\n";
                        cout << "   o Otherwise, move front to the next circular position.\n";
                        cout << "4. Display that the customer has been served.\n";
                        break;

                    case 3:
                        drawTitleBox("Peek / Front (See Next Customer)");
                        cout << "Purpose: Identify which customer will be served next.\n\n";
                        cout << "Steps:\n";
                        cout << "1. Check if the queue is empty.\n";
                        cout << "2. If empty, display no customer is waiting.\n";
                        cout << "3. If not empty, show the customer at the front.\n";
                        break;

                    case 4:
                        drawTitleBox("isEmpty (Circular Queue)");
                        cout << "Steps:\n";
                        cout << "1. If front is -1, the circular queue is empty.\n";
                        cout << "2. Otherwise, it is not empty.\n";
                        break;

                    case 5:
                        drawTitleBox("isFull (Circular Queue)");
                        cout << "Steps:\n";
                        cout << "1. If the next circular position of rear equals front, the queue is full.\n";
                        cout << "2. Otherwise, it is not full.\n";
                        break;

                    case 0:
                        setColor(11);
                        cout << "Returning to Queue Type Menu...\n";
                        setColor(7);
                        break;

                    default:
                        setColor(12);
                        cout << "Invalid choice! Try again.\n";
                        setColor(7);
                }

              if (queueChoice != 0) pauseAndWait();
           }
			 while (queueChoice != 0);
        }

        else if (queueTypeChoice == 0) {
            setColor(11);
            cout << "Returning to Algorithm Menu...\n";
            setColor(7);
           // pauseAndWait();
        }

        else {
            setColor(12);
            cout << "Invalid choice! Try again.\n";
            setColor(7);
            pauseAndWait();
        }
    } while (queueTypeChoice != 0);

            setColor(7);
            pauseAndWait();
        } else {
            setColor(12);
            cout << "Invalid choice.\n";
            setColor(7);
            pauseAndWait();
        }
    }
}

// ---------------------- CODE MODE (dynamic array with 30 hardcoded customers) ----------------------

// Dynamic array state
Customer *dynArr = nullptr;
int arrSize = 0;
int arrCapacity = 0;
bool isSortedById = false;

// Hardcoded 30 customers
Customer initial30[] = {
    {1001, "Ali Khan", 25000.50},
    {1002, "Sara Ahmed", 40200.00},
    {1003, "Usman Ali", 18000.25},
    {1004, "Ayesha Noor", 52800.75},
    {1005, "Hassan Raza", 120000.00},
    {1006, "Fatima Zafar", 7600.00},
    {1007, "Bilal Qureshi", 33400.40},
    {1008, "Zainab Malik", 4500.60},
    {1009, "Omar Farooq", 67000.90},
    {1010, "Hira Khan", 29500.00},
    {1011, "Raza Hassan", 1500.00},
    {1012, "Mariam Shah", 9800.30},
    {1013, "Naveed Akram", 21400.00},
    {1014, "Sadia Iqbal", 37200.10},
    {1015, "Waseem Ahmad", 45900.75},
    {1016, "Laila Rafi", 8800.00},
    {1017, "Tariq Jamil", 12000.50},
    {1018, "Nida Karim", 22100.00},
    {1019, "Kamran Tariq", 50100.25},
    {1020, "Sana Mir", 30500.00},
    {1021, "Adil Shah", 16000.60},
    {1022, "Sumbul Farooq", 41000.20},
    {1023, "Zafar Iqbal", 2200.00},
    {1024, "Noreen Liaqat", 17000.00},
    {1025, "Faisal Munir", 67200.00},
    {1026, "Huma Siddiq", 9900.90},
    {1027, "Irfan Aziz", 14400.00},
    {1028, "Shazia Bano", 8600.50},
    {1029, "Junaid Khan", 31000.00},
    {1030, "Rameez Alam", 54000.60}
};

// Initialize dynamic array with hardcoded 30 customers
void initDynamicArrayFromHardcoded() {
    int n = sizeof(initial30) / sizeof(initial30[0]); // should be 30
    arrCapacity = max(50, n * 2);
    dynArr = new Customer[arrCapacity];
    arrSize = 0;
    for (int i = 0; i < n; ++i) {
        dynArr[arrSize++] = initial30[i];
    }
    isSortedById = false;
}

// Resize dynamic array when needed (double capacity)
void ensureCapacity(int minCapacity = 0) 
{
    if (minCapacity <= arrCapacity && arrSize < arrCapacity) return;
    int newCap = max((arrCapacity == 0 ? 1 : arrCapacity * 2), max(arrCapacity + 1, minCapacity));
    Customer *newArr = new Customer[newCap];
    for (int i = 0; i < arrSize; ++i) newArr[i] = dynArr[i];
    delete [] dynArr;
    dynArr = newArr;
    arrCapacity = newCap;
}

// Display single row
void printCustomerRow(const Customer &c) {
    cout << left << setw(8) << c.id
         << left << setw(25) << c.name
         << right << setw(12) << fixed << setprecision(2) << c.balance << endl;
}

// Display all customers
void displayAllDynamic() {
    if (arrSize == 0) {
        cout << "No customers in the system.\n";
        return;
    }
    setColor(10);
    cout << left << setw(8) << "ID" << left << setw(25) << "Name" << right << setw(12) << "Balance" << endl;
    setColor(7);
    sepLine();
    for (int i = 0; i < arrSize; ++i) printCustomerRow(dynArr[i]);
}

// Find index by ID (linear)
int findIndexByIdDynamic(int id) {
    for (int i = 0; i < arrSize; ++i) {
        if (dynArr[i].id == id) return i;
    }
    return -1;
}

// Find index by name (case-insensitive partial)
int findIndexByNameDynamic(const string &name) {
    string t = toLowerStr(name);
    for (int i = 0; i < arrSize; ++i) {
        if (toLowerStr(dynArr[i].name).find(t) != string::npos) return i;
    }
    return -1;
}

// Bubble sort by ID
void bubbleSortByIdDynamic(bool ascending = true) {
    for (int i = 0; i < arrSize - 1; ++i) {
        for (int j = 0; j < arrSize - 1 - i; ++j) {
            bool cond = ascending ? (dynArr[j].id > dynArr[j+1].id) : (dynArr[j].id < dynArr[j+1].id);
            if (cond) swap(dynArr[j], dynArr[j+1]);
        }
    }
    isSortedById = ascending;
}

// Bubble sort by Name
void bubbleSortByNameDynamic(bool ascending = true) {
    for (int i = 0; i < arrSize - 1; ++i) {
        for (int j = 0; j < arrSize - 1 - i; ++j) {
            string a = toLowerStr(dynArr[j].name);
            string b = toLowerStr(dynArr[j+1].name);
            bool cond = ascending ? (a > b) : (a < b);
            if (cond) swap(dynArr[j], dynArr[j+1]);
        }
    }
    isSortedById = false;
}

// Bubble sort by Balance
void bubbleSortByBalanceDynamic(bool ascending = true) {
    for (int i = 0; i < arrSize - 1; ++i) {
        for (int j = 0; j < arrSize - 1 - i; ++j) {
            bool cond = ascending ? (dynArr[j].balance > dynArr[j+1].balance) : (dynArr[j].balance < dynArr[j+1].balance);
            if (cond) swap(dynArr[j], dynArr[j+1]);
        }
    }
    isSortedById = false;
}

// Linear search by ID (returns index)
int linearSearchByIdDynamic(int id) {
    return findIndexByIdDynamic(id);
}

// Binary search by ID (requires sorted)
int binarySearchByIdDynamic(int id) {
    if (!isSortedById) {
        cout << "Array not sorted by ID. Binary search requires sorting by ID first.\n";
        return -1;
    }
    int low = 0, high = arrSize - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dynArr[mid].id == id) return mid;
        else if (dynArr[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Insert operations (start, end, position)
bool insertAtEndDynamic(const Customer &c) {
    // uniqueness check
    if (findIndexByIdDynamic(c.id) != -1) return false;
    ensureCapacity();
    dynArr[arrSize++] = c;
    isSortedById = false;
    return true;
}

bool insertAtStartDynamic(const Customer &c) {
    if (findIndexByIdDynamic(c.id) != -1) return false;
    ensureCapacity();
    for (int i = arrSize - 1; i >= 0; --i) dynArr[i+1] = dynArr[i];
    dynArr[0] = c;
    ++arrSize;
    isSortedById = false;
    return true;
}

bool insertAtPositionDynamic(const Customer &c, int pos) {
    if (pos < 0 || pos > arrSize) return false;
    if (findIndexByIdDynamic(c.id) != -1) return false;
    ensureCapacity();
    for (int i = arrSize - 1; i >= pos; --i) dynArr[i+1] = dynArr[i];
    dynArr[pos] = c;
    ++arrSize;
    isSortedById = false;
    return true;
}

// Delete operations
bool deleteAtStartDynamic() {
    if (arrSize == 0) return false;
    for (int i = 1; i < arrSize; ++i) dynArr[i-1] = dynArr[i];
    --arrSize;
    return true;
}

bool deleteAtEndDynamic() {
    if (arrSize == 0) return false;
    --arrSize;
    return true;
}

bool deleteAtPositionDynamic(int pos) {
    if (pos < 0 || pos >= arrSize) return false;
    for (int i = pos + 1; i < arrSize; ++i) dynArr[i-1] = dynArr[i];
    --arrSize;
    return true;
}

bool deleteByIdDynamic(int id) {
    int idx = findIndexByIdDynamic(id);
    if (idx == -1) return false;
    return deleteAtPositionDynamic(idx);
}

// Update customer by ID
bool updateCustomerByIdDynamic(int id, const string &newName, double newBalance, bool changeName, bool changeBalance) 
{
    int idx = findIndexByIdDynamic(id);
    if (idx == -1) return false;
    if (changeName) dynArr[idx].name = newName;
    if (changeBalance) dynArr[idx].balance = newBalance;
    return true;
}

// Deposit / Withdraw
bool depositDynamic(int id, double amount) {
    int idx = findIndexByIdDynamic(id);
    if (idx == -1) return false;
    if (amount <= 0) return false;
    dynArr[idx].balance += amount;
    return true;
}

bool withdrawDynamic(int id, double amount) {
    int idx = findIndexByIdDynamic(id);
    if (idx == -1) return false;
    if (amount <= 0) return false;
    if (dynArr[idx].balance < amount) return false;
    dynArr[idx].balance -= amount;
    return true;
}

// Print single customer detailed
void printCustomerDetailed(const Customer &c) {
    setColor(10);
    cout << "ID: " << c.id << "\nName: " << c.name << "\nBalance: " << fixed << setprecision(2) << c.balance << endl;
    setColor(7);
}

// Reset dynamic array to initial hardcoded 30
void resetDynamicToInitial() {
    delete [] dynArr;
    initDynamicArrayFromHardcoded();
}

// ---------------------- CODE MODE (ARRAY) ----------------------
void codeMode() {
    resetDynamicToInitial();
    while (true) {
        system("cls");
        drawTitleBox("CODE MODE - DYNAMIC ARRAY (Regular Account) ");
        setColor(10);
        cout << "\nChoose operation (1-13) or 0 to return to Welcome Page:\n\n";
        cout << "1. Display all customers\n";
        cout << "2. Insert customer (Start / End / Position)\n";
        cout << "3. Delete customer (Start / End / Position / By ID)\n";
        cout << "4. Update customer (By ID)\n";
        cout << "5. Find customer (By ID / By Name)\n";
        cout << "6. Linear Search (By ID)\n";
        cout << "7. Binary Search (By ID) [requires sorted by ID]\n";
        cout << "8. Sort (Bubble Sort) - choose key\n";
        cout << "9. Deposit / Withdraw\n";
        cout << "10. Show current array size & capacity\n";
        cout << "11. Reset to initial hardcoded data\n";
        cout << "12. Print single customer by index\n";
        cout << "13. Show quick algorithm hints\n";
        cout << "0. Return to Welcome Page\n";
        setColor(7);
        cout << "\nEnter your choice: ";
        int ch;
		 cin >> ch;
        system("cls");
        drawTitleBox("CODE MODE - DYNAMIC ARRAY");

        if (ch == 0) return;

        switch (ch) {
            case 1: {
                setColor(11);
                cout << "\n--- All Customers (" << arrSize << ") ---\n\n";
                setColor(7);
                displayAllDynamic();
                break;
            }
            case 2: {
                setColor(11);
                cout << "\n--- Insert Customer ---\n";
                setColor(10);
                cout << "Enter insertion type:\n1. Start\n2. End\n3. Position\nChoice: ";
                setColor(7);
                int t;
				 cin >> t;
                Customer c;
                cout << "Enter new Customer ID (integer): ";
				 cin >> c.id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Name: "; 
				getline(cin, c.name);
                cout << "Enter Balance: ";
				 cin >> c.balance;
				  bool ok = false;
                if (t == 1) ok = insertAtStartDynamic(c);
                else if (t == 2) ok = insertAtEndDynamic(c);
                else if (t == 3) {
                    cout << "Enter position (0 - " << arrSize << "): ";
                    int pos; cin >> pos;
                    ok = insertAtPositionDynamic(c, pos);
                }
				 else cout << "Invalid insertion type.\n";
                if (ok) { 
				setColor(10); 
				cout << "Inserted successfully.\n";
				 setColor(7); }
                else { 
				setColor(12); 
				cout << "Insertion failed (invalid position or duplicate ID).\n"; 
				setColor(7); }
                break;
            }
            case 3: {
                setColor(11);
                cout << "\n--- Delete Customer ---\n";
                setColor(10);
                cout << "Enter deletion type:\n1. Start\n2. End\n3. Position\n4. By ID\nChoice: ";
                setColor(7);
                int t; cin >> t;
                bool ok = false;
                if (t == 1) ok = deleteAtStartDynamic();
                else if (t == 2) ok = deleteAtEndDynamic();
                else if (t == 3) {
                    cout << "Enter position (0 - " << arrSize - 1 << "): ";
                    int pos; cin >> pos;
                    ok = deleteAtPositionDynamic(pos);
                }
                else if (t == 4) {
                    cout << "Enter ID to delete: ";
                    int id; cin >> id;
                    int idx = findIndexByIdDynamic(id);
                    if (idx != -1 && dynArr[idx].balance > 0) {
                        setColor(12);
                        cout << "Warning: Account has non-zero balance (" << dynArr[idx].balance << ").\n";
                        setColor(10);
                        cout << "Proceed with deletion? 1-Yes 2-No: ";
                        int r; cin >> r;
                        if (r == 2) { ok = false; 
						cout << "Deletion cancelled.\n"; }
                        else ok = deleteByIdDynamic(id);
                    } 
					else ok = deleteByIdDynamic(id);
                } 
				else cout << "Invalid choice.\n";

                if (ok) { 
				setColor(10);
				 cout << "Deletion successful.\n";
				  setColor(7);
				   }
                else 
				{
				 setColor(12);
				 cout << "Deletion failed (empty array or not found).\n";
				  setColor(7);
				   }
                break;
            }
            case 4: {
                setColor(11);
                cout << "\n--- Update Customer (By ID) ---\n";
                setColor(10);
                cout << "Enter Customer ID to update: ";
                int id; cin >> id;
                int idx = findIndexByIdDynamic(id);
                if (idx == -1) {
                    setColor(12);
                    cout << "Customer with ID " << id << " not found.\n";
                    setColor(7);
                } else {
                    setColor(10);
                    cout << "Found: \n";
                    setColor(7);
                    printCustomerDetailed(dynArr[idx]);
                    cout << "\nWhat to update? (1-Name, 2-Balance, 3-Both): ";
                    int t; cin >> t;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    string newName;
                    double newBalance = dynArr[idx].balance;
                    bool changeName = false, changeBalance = false;
                    if (t == 1 || t == 3) 
					{
                        cout << "Enter new name: ";
						 getline(cin, newName);
                        changeName = true;
                    }
                    if (t == 2 || t == 3) 
					{
                        cout << "Enter new balance: "; 
						cin >> newBalance;
                        changeBalance = true;
                    }
                    bool ok = updateCustomerByIdDynamic(id, newName, newBalance, changeName, changeBalance);
                    if (ok) { 
					setColor(10); 
					cout << "Update successful.\n"; 
					setColor(7); }
                    else { 
					setColor(12); 
					cout << "Update failed.\n"; 
					setColor(7); }
                }
                break;
            }
            case 5: {
                setColor(11);
                cout << "\n--- Find Customer ---\n";
                setColor(10);
                cout << "Search by: 1) ID  2) Name\nChoice: ";
                setColor(7);
                int t; cin >> t;
                if (t == 1) {
                    cout << "Enter ID: ";
                    int id;
					 cin >> id;
                    int idx = findIndexByIdDynamic(id);
                    if (idx == -1) { setColor(12);
					 cout << "Not found.\n";
					  setColor(7);
					   }
                    else {
                        setColor(10);
                        cout << "Found:\n";
                        setColor(7);
                        printCustomerDetailed(dynArr[idx]);
                    }
                } else if (t == 2) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter full or partial Name: ";
                    string name;
					 getline(cin, name);
                    int idx = findIndexByNameDynamic(name);
                    if (idx == -1) {
					 setColor(12);
					 cout << "Not found (no partial match).\n"; 
					 setColor(7); }
                    else {
                        setColor(10);
                        cout << "Found (first match):\n";
                        setColor(7);
                        printCustomerDetailed(dynArr[idx]);
                    }
                } else {
                    setColor(12);
                    cout << "Invalid choice.\n";
                    setColor(7);
                }
                break;
            }
            case 6: {
                setColor(11);
                cout << "\n--- Linear Search by ID ---\n";
                setColor(10);
                cout << "Enter ID: "; 
				int id; 
				cin >> id;
                int idx = linearSearchByIdDynamic(id);
                if (idx == -1) { 
				setColor(12);
				 cout << "Not found.\n"; 
				 setColor(7); }
                else {
				 setColor(10);
				  cout << "Found at index " << idx << ":\n";
				   setColor(7);
				 printCustomerDetailed(dynArr[idx]);
				  }
                break;
            }
            case 7: {
                setColor(11);
                cout << "\n--- Binary Search by ID ---\n";
                setColor(10);
                cout << "Note: Array must be sorted by ID ascending.\n";
                if (!isSortedById) {
                    cout << "Array is NOT currently sorted by ID.\n";
                    cout << "Would you like to sort by ID now? (1-Yes / 2-No): ";
                    int r; cin >> r;
                    if (r == 1) { 
					bubbleSortByIdDynamic(true); 
					cout << "Array sorted by ID (ascending).\n"; 
					
					}
                }
                cout << "Enter ID to find: "; 
				int id;
				 cin >> id;
                int idx = binarySearchByIdDynamic(id);
                if (idx == -1) {
				 setColor(12); 
				 cout << "Not found (or array not sorted by ID).\n"; 
				setColor(7);
				 }
                else
				 {
				 setColor(10); 
				cout << "Found at index " << idx << ":\n"; 
				setColor(7); 
				printCustomerDetailed(dynArr[idx]);
				 }
                break;
            }
            case 8: {
                setColor(11);
                cout << "\n--- Sort (Bubble Sort) ---\n";
                setColor(10);
                cout << "Sort by:\n1. ID (ascending)\n2. ID (descending)\n3. Name (A-Z)\n4. Name (Z-A)\n5. Balance (ascending)\n6. Balance (descending)\nChoice: ";
                setColor(7);
                int s; 
				cin >> s;
                switch (s) {
                    case 1:
					 bubbleSortByIdDynamic(true);
					 cout << "Sorted by ID ascending.\n"; 
					 break;
                    case 2: 
					bubbleSortByIdDynamic(false);
					 cout << "Sorted by ID descending.\n"; break;
                    case 3: 
					bubbleSortByNameDynamic(true); 
					cout << "Sorted by Name A-Z.\n"; 
					break;
                    case 4: 
					bubbleSortByNameDynamic(false);
					 cout << "Sorted by Name Z-A.\n"; 
					 break;
                    case 5: 
					bubbleSortByBalanceDynamic(true);
					 cout << "Sorted by Balance ascending.\n";
					  break;
                    case 6:
					 bubbleSortByBalanceDynamic(false);
					 cout << "Sorted by Balance descending.\n"; 
					 break;
                    default: 
					cout << "Invalid sort choice.\n"; 
					break;
                }
                break;
            }
            case 9: {
                setColor(11);
                cout << "\n--- Deposit / Withdraw ---\n";
                setColor(10);
                cout << "Choose: 1) Deposit  2) Withdraw\nChoice: ";
                setColor(7);
                int t; cin >> t;
                if (t == 1) {
                    cout << "Enter ID: ";
					 int id; 
					cin >> id;
                    cout << "Enter amount to deposit: ";
					 double amt; 
					 cin >> amt;
                    if (depositDynamic(id, amt)) { 
					setColor(10); 
					cout << "Deposit successful.\n";
					 setColor(7);
					 }
                    else { 
					setColor(12); 
					cout << "Deposit failed (invalid ID or amount).\n";
					 setColor(7);
					  }
                } else if (t == 2) {
                    cout << "Enter ID: ";
					 int id; 
					 cin >> id;
                    cout << "Enter amount to withdraw: "; 
					double amt; 
					cin >> amt;
                    int idx = findIndexByIdDynamic(id);
                    if (idx == -1) { setColor(12); 
					cout << "Account not found.\n";
					 setColor(7); 
					 }
                    else if (dynArr[idx].balance < amt) { 
					setColor(12); 
					cout << "Insufficient funds.\n";
					 setColor(7); 
					 }
                    else {
                        if (withdrawDynamic(id, amt)) { 
						setColor(10); 
						cout << "Withdrawal successful.\n";
						 setColor(7);
						  }
                        else { setColor(12); 
						cout << "Withdrawal failed (invalid amount).\n"; 
						
						setColor(7); }
                    }
                } else {
                    setColor(12); 
					cout << "Invalid transaction choice.\n"; 
					setColor(7);
                }
                break;
            }
            case 10: {
                setColor(11);
                cout << "\nCurrent array size: " << arrSize << "    capacity: " << arrCapacity << endl;
                cout << "Is sorted by ID? " << (isSortedById ? "Yes" : "No") << endl;
                setColor(7);
                break;
            }
            case 11: {
                resetDynamicToInitial();
                setColor(10);
                cout << "Reset to initial hardcoded 30 customers.\n";
                setColor(7);
                break;
            }
            case 12: {
                cout << "Enter index (0 - " << arrSize - 1 << "): ";
                int idx; cin >> idx;
                if (idx < 0 || idx >= arrSize) { 
				setColor(12);
				 cout << "Invalid index.\n";
				  setColor(7); }
                else printCustomerDetailed(dynArr[idx]);
                break;
            }
            case 13: {
                setColor(11);
                cout << "\n--- Quick Algorithm Hints ---\n";
                setColor(10);
                cout << "Insert at pos: shift right from last to pos and place new.\n";
                cout << "Delete at pos: shift left from pos+1 to end.\n";
                cout << "Linear search: loop from 0..n-1 compare id.\n";
                cout << "Binary search: requires sorted-by-id and use low/mid/high.\n";
                setColor(7);
                break;
            }
            default:
                setColor(12);
                cout << "Invalid choice.\n";
                setColor(7);
        }

        pauseAndWait();
    }
}

// ---------------------- LINKED LIST CODE MODE (full working functions) ----------------------
LLNode* headLL = nullptr;

// Insert at end (LL)
bool insertAtEndLL(const LLNode& cnode) {
    // check duplicate id
    LLNode* t = headLL;
    while (t) {
        if (t->id == cnode.id) return false;
        t = t->next;
    }
    LLNode* newNode = new LLNode(cnode.id, cnode.name, cnode.balance);
    if (!headLL) headLL = newNode;
    else {
        LLNode* cur = headLL;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }
    return true;
}

// Display all (LL)
void displayAllLL() {
    if (!headLL) {
        setColor(12);
        cout << "No customers in the system.\n";
        setColor(7);
        return;
    }
    setColor(10);
    cout << left << setw(8) << "ID"
         << left << setw(25) << "Name"
         << right << setw(12) << "Balance" << endl;
    cout << string(50, '-') << endl;
    setColor(7);

    LLNode* temp = headLL;
    while (temp) {
        cout << left << setw(8) << temp->id<< left << setw(25) << temp->name << right << setw(12) << fixed << setprecision(2) << temp->balance << endl;
        temp = temp->next;
    }
}

// Find by ID (LL)
LLNode* findByIdLL(int id) {
    LLNode* temp = headLL;
    while (temp) {
        if (temp->id == id) 
		return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Delete by ID (LL)
bool deleteByIdLL(int id) {
    if (!headLL) return false;
    if (headLL->id == id) 
	{
        LLNode* del = headLL;
        headLL = headLL->next;
        delete del;
        return true;
    }
    LLNode* cur = headLL;
    while (cur->next && cur->next->id != id) 
	cur = cur->next;
    if (!cur->next) 
	return false;
    LLNode* del = cur->next;
    cur->next = cur->next->next;
    delete del;
    return true;
}

// Update (LL)
void updateCustomerLL_menu() {
    int id;
    cout << "Enter Account ID to update: ";
    cin >> id;

    LLNode* c = findByIdLL(id);
    if (!c) {
        cout << "ID not found!" << endl;
        return;  // stop if ID doesn't exist
    }

    char choiceName, choiceBalance;
    string newName;
    double newBalance;

    cout << "Do you want to update the Name? (y/n): ";
    cin >> choiceName;
    bool changeName = (choiceName == 'y' || choiceName == 'Y');

    if (changeName) {
        cout << "Enter new Name: ";
        cin.ignore(); // clear the input buffer
        getline(cin, newName);
    }

    cout << "Do you want to update the Balance? (y/n): ";
    cin >> choiceBalance;
    bool changeBalance = (choiceBalance == 'y' || choiceBalance == 'Y');

    if (changeBalance) {
        cout << "Enter new Balance: ";
        cin >> newBalance;
        if (newBalance < 0) {
            cout << "Invalid balance!" << endl;
            return;
        }
    }

    if (!changeName && !changeBalance) {
        cout << "Nothing to update!" << endl;
        return;
    }

    if (changeName) c->name = newName;
    if (changeBalance) c->balance = newBalance;

    cout << "Customer details updated successfully!" << endl;
}


void deposit() {
    int id;
    double amount;

    cout << "Enter Account ID: ";
    cin >> id;

    LLNode* c = findByIdLL(id);  // make sure findByIdLL is declared before this function
    if (!c) {
        cout << "ID not found!" << endl;
        return;   // stops the deposit function instantly
    }

    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid deposit amount!" << endl;
        return;
    }

    c->balance += amount;
    cout << "Amount deposited successfully!" << endl;
}



// Withdraw (LL)
void withdraw() {
    int id;
    double amount;

    cout << "Enter Account ID: ";
    cin >> id;

    LLNode* c = findByIdLL(id);  // make sure findByIdLL is declared before this function
    if (!c) {
        cout << "ID not found!" << endl;
        return;   // stops the function instantly if ID is wrong
    }

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid withdrawal amount!" << endl;
        return;
    }

    if (c->balance < amount) {
        cout << "Insufficient balance!" << endl;
        return;
    }

    c->balance -= amount;
    cout << "Amount withdrawn successfully!" << endl;
}

// Hardcoded last 15 for LL
void initHardcodedLast15LL() {
    // These match the last 15 from the array initial data
    LLNode tempList[] = {
        LLNode(1016, "Laila Rafi", 8800.00), 
		LLNode(1017, "Tariq Jamil", 12000.50),
        LLNode(1018, "Nida Karim", 22100.00), 
		LLNode(1019, "Kamran Tariq", 50100.25),
        LLNode(1020, "Sana Mir", 30500.00), 
		LLNode(1021, "Adil Shah", 16000.60),
        LLNode(1022, "Sumbul Farooq", 41000.20),
		LLNode(1023, "Zafar Iqbal", 2200.00),
        LLNode(1024, "Noreen Liaqat", 17000.00), 
		LLNode(1025, "Faisal Munir", 67200.00),
        LLNode(1026, "Huma Siddiq", 9900.90), 
		LLNode(1027, "Irfan Aziz", 14400.00),
        LLNode(1028, "Shazia Bano", 8600.50),
	    LLNode(1029, "Junaid Khan", 31000.00),
        LLNode(1030, "Rameez Alam", 54000.60)
    };
    int n = sizeof(tempList) / sizeof(tempList[0]);
    for (int i = 0; i < n; ++i) insertAtEndLL(tempList[i]);
}

// Linked List Code Mode menu (complete)
void linkedListCodeMode() {
    // initialize LL with last 15 (so user sees some data)
    // clear any existing list first (safety)
    while (headLL) { LLNode* t = headLL; headLL = headLL->next; delete t; }
    initHardcodedLast15LL();

    int choice;
    do {
        system("cls");
        drawTitleBox("CODE MODE - LINKED LIST IMPLEMENTATION");
        setColor(10);
        cout << "\n1. Display All Customers\n";
        cout << "2. Search by ID\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Update Customer\n";
        cout << "6. Delete Customer\n";
        cout << "7. Add New Customer\n";
        cout << "0. Back to Main Menu\n";
        setColor(7);
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayAllLL();
        } else if (choice == 2) {
            int id;
            cout << "Enter ID: ";
            cin >> id;
            LLNode* c = findByIdLL(id);
            if (c) {
                setColor(10);
                cout << "Found -> ID: " << c->id << ", Name: " << c->name << ", Balance: " << c->balance << endl;
                setColor(7);
            } else {
                setColor(12);
                cout << "Customer not found.\n";
                setColor(7);
            }
        } else if (choice == 3) {
        	deposit();
		}
			
		 else if (choice == 4){
        	
        	withdraw();
		}
		  else if (choice == 5) 
		{
			updateCustomerLL_menu();
		}
		
		
	 else if (choice == 6) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            if (deleteByIdLL(id))
			 {
			  setColor(10); 
			  cout << "Customer deleted.\n";
			   }
            else { 
			setColor(12); 
			cout << "Delete failed.\n";
			 }
            setColor(7);
        } else if (choice == 7) {
            LLNode tmp;
            cout << "Enter ID: "; 
			cin >> tmp.id;
            cin.ignore();
            cout << "Enter Name: ";
			 getline(cin, tmp.name);
            cout << "Enter Balance: "; 
			cin >> tmp.balance;
            if (insertAtEndLL(tmp)) {
			 setColor(10); cout << "Customer added.\n"; 
			 }
            else { setColor(12); 
			cout << "Add failed (duplicate ID).\n";
			 }
            setColor(7);
        } else if (choice == 0) {
            // go back
        } else {
            setColor(12);
            cout << "Invalid choice!\n";
            setColor(7);
        }

        pauseAndWait();
    } while (choice != 0);
}
// ==========================
// DOUBLY LINKED LIST NODE
// ==========================
struct DLLNode {
    int id;
    string name;
    double balance;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(int i, string n, double b) : id(i), name(n), balance(b), prev(nullptr), next(nullptr) {}
};

// ==========================
// DLL HEAD POINTER
// ==========================
DLLNode* headDLL = nullptr;

// --------------------------
// INSERT AT END (DLL)
// --------------------------
bool insertAtEndDLL(const DLLNode& cnode) {
    // check duplicate
    DLLNode* t = headDLL;
    while (t) {
        if (t->id == cnode.id) return false;
        t = t->next;
    }
    DLLNode* newNode = new DLLNode(cnode.id, cnode.name, cnode.balance);
    if (!headDLL) headDLL = newNode;
    else {
        DLLNode* cur = headDLL;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
        newNode->prev = cur;
    }
    return true;
}

// --------------------------
// DISPLAY ALL (DLL)
// --------------------------
void displayAllDLL() {
    if (!headDLL) {
        setColor(12);
        cout << "No customers in the system.\n";
        setColor(7);
        return;
    }
    setColor(10);
    cout << left << setw(8) << "ID"
         << left << setw(25) << "Name"
         << right << setw(12) << "Balance" << endl;
    cout << string(50, '-') << endl;
    setColor(7);

    DLLNode* temp = headDLL;
    while (temp) {
        cout << left << setw(8) << temp->id
             << left << setw(25) << temp->name
             << right << setw(12) << fixed << setprecision(2) << temp->balance << endl;
        temp = temp->next;
    }
}

// --------------------------
// FIND BY ID (DLL)
// --------------------------
DLLNode* findByIdDLL(int id) {
    DLLNode* temp = headDLL;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// --------------------------
// DELETE BY ID (DLL)
// --------------------------
bool deleteByIdDLL(int id) {
    if (!headDLL) return false;
    DLLNode* temp = headDLL;
    while (temp && temp->id != id) temp = temp->next;
    if (!temp) return false;

    if (temp->prev) temp->prev->next = temp->next;
    else headDLL = temp->next;

    if (temp->next) temp->next->prev = temp->prev;

    delete temp;
    return true;
}

// --------------------------
// UPDATE (DLL)
// --------------------------


void updateCustomerDLL_menu() {
    int id;
    cout << "Enter Account ID to update: ";
    cin >> id;

    DLLNode* c = findByIdDLL(id);
    if (!c) {
        cout << "ID not found!" << endl;
        return;  // stop if ID doesn't exist
    }

    char choiceName, choiceBalance;
    string newName;
    double newBalance;

    cout << "Do you want to update the Name? (y/n): ";
    cin >> choiceName;
    bool changeName = (choiceName == 'y' || choiceName == 'Y');

    if (changeName) {
        cout << "Enter new Name: ";
        cin.ignore();  // clear the input buffer
        getline(cin, newName);
    }

    cout << "Do you want to update the Balance? (y/n): ";
    cin >> choiceBalance;
    bool changeBalance = (choiceBalance == 'y' || choiceBalance == 'Y');

    if (changeBalance) {
        cout << "Enter new Balance: ";
        cin >> newBalance;
        if (newBalance < 0) {
            cout << "Invalid balance!" << endl;
            return;
        }
    }

    if (!changeName && !changeBalance) {
        cout << "Nothing to update!" << endl;
        return;
    }

    if (changeName) c->name = newName;
    if (changeBalance) c->balance = newBalance;

    cout << "Customer details updated successfully!" << endl;
}

// --------------------------
// DEPOSIT (DLL)
// --------------------------
void depositDLL_menu() {
    int id;
    double amount;

    cout << "Enter Account ID: ";
    cin >> id;

    DLLNode* c = findByIdDLL(id);  // check if ID exists
    if (!c) {
        cout << "ID not found!" << endl;
        return;  // stop instantly if ID is wrong
    }

    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid deposit amount!" << endl;
        return;
    }

    c->balance += amount;
    cout << "Amount deposited successfully!" << endl;
}



// --------------------------
// WITHDRAW (DLL)
// --------------------------


void withdrawDLL_menu() {
    int id;
    double amount;

    cout << "Enter Account ID: ";
    cin >> id;

    DLLNode* c = findByIdDLL(id);  // check if ID exists
    if (!c) {
        cout << "ID not found!" << endl;
        return;  // stop instantly if ID is wrong
    }

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid withdrawal amount!" << endl;
        return;
    }

    if (c->balance < amount) {
        cout << "Insufficient balance!" << endl;
        return;
    }

    c->balance -= amount;
    cout << "Amount withdrawn successfully!" << endl;
}



// --------------------------
// HARD-CODED LAST 15 DLL
// --------------------------
void initHardcodedLast15DLL() {
    DLLNode tempList[] = {
        DLLNode(1016, "Laila Rafi", 8800.00),
        DLLNode(1017, "Tariq Jamil", 12000.50),
        DLLNode(1018, "Nida Karim", 22100.00),
        DLLNode(1019, "Kamran Tariq", 50100.25),
        DLLNode(1020, "Sana Mir", 30500.00),
        DLLNode(1021, "Adil Shah", 16000.60),
        DLLNode(1022, "Sumbul Farooq", 41000.20),
        DLLNode(1023, "Zafar Iqbal", 2200.00),
        DLLNode(1024, "Noreen Liaqat", 17000.00),
        DLLNode(1025, "Faisal Munir", 67200.00),
        DLLNode(1026, "Huma Siddiq", 9900.90),
        DLLNode(1027, "Irfan Aziz", 14400.00),
        DLLNode(1028, "Shazia Bano", 8600.50),
        DLLNode(1029, "Junaid Khan", 31000.00),
        DLLNode(1030, "Rameez Alam", 54000.60)
    };
    int n = sizeof(tempList)/sizeof(tempList[0]);
    for(int i=0;i<n;i++) insertAtEndDLL(tempList[i]);
}

// --------------------------
// DLL CODE MODE MENU
// --------------------------
void doublyLinkedListCodeMode() {
    // Clear old list if exists
    while(headDLL) { DLLNode* t = headDLL; headDLL = headDLL->next; delete t; }
    initHardcodedLast15DLL();

    int choice;
    do {
        system("cls");
        drawTitleBox("CODE MODE - DOUBLY LINKED LIST");
        setColor(10);
        cout << "\n1. Display All Customers\n";
        cout << "2. Search by ID\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Update Customer\n";
        cout << "6. Delete Customer\n";
        cout << "7. Add New Customer\n";
        cout << "0. Back to Main Menu\n";
        setColor(7);
        cout << "Enter your choice: ";
        cin >> choice;

        int id;
        string name;
        double balance;
        DLLNode* acc;

        switch(choice) {
            case 1: displayAllDLL(); break;
            case 2:
                cout << "Enter ID to search: ";
                cin >> id;
                acc = findByIdDLL(id);
                if(acc) cout << "Found: " << acc->id << " " << acc->name << " " << acc->balance << "\n";
                else cout << "Customer not found.\n";
                break;
            case 3:
            depositDLL_menu();
              
                break;
            case 4:
            	withdrawDLL_menu() ;
              
                break;
            case 5:
              
			  
			   updateCustomerDLL_menu() ;
			  
			  
                break;
            case 6:
                cout << "Enter ID to delete: ";
                cin >> id;
                if(deleteByIdDLL(id)) cout << "Deletion successful.\n";
                else cout << "Customer not found.\n";
                break;
            case 7:
                cout << "Enter ID, Name, Balance: ";
                cin >> id >> ws;
                getline(cin, name);
                cin >> balance;
                if(insertAtEndDLL(DLLNode(id, name, balance))) cout << "Customer added successfully.\n";
                else cout << "Duplicate ID! Cannot add.\n";
                break;
            case 0: cout << "Returning to main menu...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
        pauseAndWait();
    } while(choice != 0);
}

//------------------------------------circular linklist------------------------------
// ==========================================================
//  UNIQUE Circular Linked List for Bank (CircBank_*)
// ==========================================================

// -------------------- Customer Node --------------------
struct CircBankNode {
    int id;
    string name;
    double balance;
    CircBankNode* next;

    CircBankNode(int i, string n, double b) {
        id = i;
        name = n;
        balance = b;
        next = nullptr;
    }
};

// -------------------- Circular Linked List Class --------------------
class CircBankList {
private:
    CircBankNode* head;

public:
    CircBankList() {
        head = nullptr;

        // Preload 15 customers
        addCustomer(101, "Alice", 5000);
        addCustomer(102, "Bob", 3000);
        addCustomer(103, "Charlie", 7000);
        addCustomer(104, "David", 4500);
        addCustomer(105, "Eva", 6000);
        addCustomer(106, "Frank", 3500);
        addCustomer(107, "Grace", 8000);
        addCustomer(108, "Henry", 2000);
        addCustomer(109, "Ivy", 9000);
        addCustomer(110, "Jack", 1000);
        addCustomer(111, "Kate", 7500);
        addCustomer(112, "Leo", 4200);
        addCustomer(113, "Mia", 6800);
        addCustomer(114, "Nina", 5100);
        addCustomer(115, "Oscar", 4700);
    }

    bool isEmpty() {
        return head == nullptr;
    }

    // -------------------- Add Customer (End Insert) --------------------
    void addCustomer(int id, string name, double balance) {
        CircBankNode* newNode = new CircBankNode(id, name, balance);

        if (isEmpty()) {
            head = newNode;
            head->next = head;
            return;
        }

        CircBankNode* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }

    // -------------------- Delete at Start --------------------
    void deleteStart() {
        if (isEmpty()) {
            cout << "List is empty!\n";
            return;
        }

        CircBankNode* temp = head;

        if (head->next == head) { // only one node
            delete head;
            head = nullptr;
            return;
        }

        CircBankNode* last = head;
        while (last->next != head)
            last = last->next;

        last->next = head->next;
        head = head->next;

        delete temp;
    }

    // -------------------- Delete at End --------------------
    void deleteEnd() {
        if (isEmpty()) {
            cout << "List is empty!\n";
            return;
        }

        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }

        CircBankNode* temp = head;
        CircBankNode* prev = nullptr;

        while (temp->next != head) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = head;
        delete temp;
    }

    // -------------------- Delete at Specific Position --------------------
    void deletePosition(int pos) {
        if (isEmpty()) {
            cout << "List is empty!\n";
            return;
        }

        if (pos == 1) {
            deleteStart();
            return;
        }

        CircBankNode* temp = head;
        CircBankNode* prev = nullptr;

        int count = 1;
        do {
            prev = temp;
            temp = temp->next;
            count++;
        } while (temp != head && count < pos);

        if (temp == head) {
            cout << "Invalid position!\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
    }

    // -------------------- Display --------------------
    void display() {
        if (isEmpty()) {
            cout << "List is empty!\n";
            return;
        }

        CircBankNode* temp = head;
        int c = 1;

        cout << "\n--- Customers in Circular Linked List ---\n";
        do {
            cout << c << ". ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Balance: $" << temp->balance << endl;

            temp = temp->next;
            c++;
        } while (temp != head);

        cout << endl;
    }
};

// ==========================================================
//     UNIQUE FUNCTION TO RUN SYSTEM (CircBankSystemMenu)
// ==========================================================
void CircBankSystemMenu() {
    CircBankList bank;
    int choice;

    do {
        system("cls");
        cout << "====== Circular Linked List - Bank Management ======\n";
        cout << "1. Delete at Start\n";
        cout << "2. Delete at End\n";
        cout << "3. Delete at Specific Position\n";
        cout << "4. Display Customers\n";
        cout << "0. Exit Circular List\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.deleteStart();
                break;
            case 2:
                bank.deleteEnd();
                break;
            case 3: {
                int pos;
                cout << "Enter position to delete: ";
                cin >> pos;
                bank.deletePosition(pos);
                break;
            }
            case 4:
                bank.display();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 0);
}

//-------------------------------------------QUEUE----------------------------------



struct BankCustomer {
    string customerName;
    string accountNumber;
};

// Already Registered Customers in Bank
BankCustomer registeredCustomers[5] = {
    {"Ali", "1001"},
    {"Ayesha", "1002"},
    {"Ahmed", "1003"},
    {"Sara", "1004"},
    {"Usman", "1005"}
};

struct TokenCustomer {
    int tokenNumber;
    string customerName;
    string accountNumber;
};

#define QUEUE_SIZE 20

class BankQueueSystem {
public:
    TokenCustomer queue[QUEUE_SIZE];
    int frontIndex, rearIndex;
    int nextToken = 1;  // Auto Token

    BankQueueSystem() {
        frontIndex = rearIndex = -1;
    }

    // Find customer from registered list
    bool findCustomer(string acc, BankCustomer &c) {
        for (int i = 0; i < 5; i++) {
            if (registeredCustomers[i].accountNumber == acc) {
                c = registeredCustomers[i];
                return true;
            }
        }
        return false;
    }

    // Check if customer already has a token
    bool isAlreadyInQueue(string acc) {
        if (frontIndex == -1) return false;
        for (int i = frontIndex; i <= rearIndex; i++) {
            if (queue[i].accountNumber == acc) {
                return true;
            }
        }
        return false;
    }

    // Add customer to queue
    void addToQueue() {
        if (rearIndex == QUEUE_SIZE - 1) {
            cout << "Queue is full.\n";
            return;
        }

        string acc;
        cout << "Enter your Account Number: ";
        cin >> acc;

        BankCustomer found;
        if (!findCustomer(acc, found)) {
            cout << "Account not found in system.\n";
            return;
        }

        if (isAlreadyInQueue(acc)) {
            cout << "You already have a token and are waiting in queue.\n";
            return;
        }

        TokenCustomer tc;
        tc.customerName = found.customerName;
        tc.accountNumber = found.accountNumber;
        tc.tokenNumber = nextToken++;

        if (frontIndex == -1) frontIndex = 0;
        queue[++rearIndex] = tc;

        cout << "\nWelcome " << tc.customerName << "!\n";
        cout << "Your Token Number is: " << tc.tokenNumber << "\n\n";
    }

    // Serve next customer
    void serveNextCustomer() {
        if (frontIndex == -1 || frontIndex > rearIndex) {
            cout << "No customers in queue.\n";
            return;
        }

        cout << "\n Dequeue Serving Customer:\n";
        cout << "Token: " << queue[frontIndex].tokenNumber << "\n";
        cout << "Name: " << queue[frontIndex].customerName << "\n";
        cout << "Account: " << queue[frontIndex].accountNumber << "\n\n";

        frontIndex++;
    }

    // Display queue
    void displayQueue() {
        if (frontIndex == -1 || frontIndex > rearIndex) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "\nCurrent Queue:\n";
        for (int i = frontIndex; i <= rearIndex; i++) {
            cout << queue[i].tokenNumber << " - " << queue[i].customerName << endl;
        }
        cout << endl;
    }
};

// Function you can call anywhere
void runBankQueueSystem() {
    BankQueueSystem bqs;
    int option;

    while (true) {
        cout << "----- Bank Token System -----\n";
        cout << "1. Customer Arrived (Get Token)\n";
        cout << "2. Serve Next Customer\n";
        cout << "3. Show Queue\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> option;
        cin.ignore();
        system("cls");

        if (option == 1) bqs.addToQueue();
        else if (option == 2) bqs.serveNextCustomer();
        else if (option == 3) bqs.displayQueue();
        else if (option == 4) break;
        else cout << "Invalid!\n";
    }
}

// -------------------------------- Stack with Dynamic Array --------------------------------
struct StackCustomer {
    int id;
    string name;
    double balance;
};

class CustomerStack {
private:
    StackCustomer* stack;
    int capacity;
    int top;

    void resize() {
        int newCap = capacity * 2;
        StackCustomer* newArr = new StackCustomer[newCap];
        for (int i = 0; i <= top; i++)
            newArr[i] = stack[i];
        delete[] stack;
        stack = newArr;
        capacity = newCap;
    }

public:
    CustomerStack() {
        capacity = 10;
        stack = new StackCustomer[capacity];
        top = -1;
    }

    ~CustomerStack() { delete[] stack; }

    bool isEmpty() { return top == -1; }

    bool idExists(int id) {
        for (int i = 0; i <= top; i++)
            if (stack[i].id == id) return true;
        return false;
    }

    void pushCustomer(StackCustomer c) {
        if (top + 1 == capacity) resize();
        stack[++top] = c;
    }

    bool popCustomer() {
        if (!isEmpty()) { top--; return true; }
        return false;
    }

    StackCustomer getTopCustomer() {
        if (!isEmpty()) return stack[top];
        return {0, "", 0.0};
    }

    void displayCustomers() {
        if (isEmpty()) { cout << "Stack is empty!\n"; return; }
        cout << "Customers in stack (top to bottom):\n";
        for (int i = top; i >= 0; i--)
            cout << "ID: " << stack[i].id
                 << " | Name: " << stack[i].name
                 << " | Balance: $" << stack[i].balance << endl;
        cout << endl;
    }

    void insertCustomer() {
        StackCustomer c;
        cout << "Enter Customer ID: ";
        cin >> c.id;

        if (idExists(c.id)) {
            cout << "Error: ID already exists!\n\n";
            return;
        }

        cin.ignore();
        cout << "Enter Customer Name: ";
        getline(cin, c.name);
        cout << "Enter Customer Balance: ";
        cin >> c.balance;

        pushCustomer(c);
        cout << "Customer added successfully!\n\n";
    }
};

// ---------------------- STACK MENU FUNCTION ----------------------
void runStackSystem() {
    CustomerStack stk;
    int choice;

    // Optional: preload some customers
    stk.pushCustomer({101, "Alice", 5000});
    stk.pushCustomer({102, "Bob", 3000});
    stk.pushCustomer({103, "Charlie", 7000});
    stk.pushCustomer({104, "Arshad", 7000});
    stk.pushCustomer({105, "Ali", 5000});
    stk.pushCustomer({106, "Amna", 5000});
    stk.pushCustomer({107, "Ahmed", 5000});
    stk.pushCustomer({108, "Azeema", 5000});
    

    do {
        system("cls");
        drawTitleBox("STACK CUSTOMER MANAGEMENT (student Account)");

        setColor(10);
        cout << "\n1. Push Customer\n";
        cout << "2. Pop Customer\n";
        cout << "3. View Top Customer\n";
        cout << "4. Display All Customers\n";
        cout << "0. Back\n";
        setColor(7);

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // avoid skipping getline

        system("cls");

        switch(choice) {
            case 1:
                stk.insertCustomer();
                pauseAndWait();
                break;

            case 2:
                if (stk.popCustomer())
                    cout << "Top customer removed successfully!\n";
                else
                    cout << "Stack is empty!\n";
                pauseAndWait();
                break;

            case 3: {
                StackCustomer topC = stk.getTopCustomer();
                if (topC.id != 0) {
                    cout << "\nTop Customer:\n";
                    cout << "ID: " << topC.id
                         << " | Name: " << topC.name
                         << " | Balance: $" << topC.balance << "\n";
                } else {
                    cout << "Stack is empty!\n";
                }
                pauseAndWait();
                break;
            }

            case 4:
                stk.displayCustomers();
                pauseAndWait();
                break;

            case 0:
                cout << "Returning to previous menu...\n";
                break;

            default:
                cout << "Invalid choice!\n";
                pauseAndWait();
        }

    } while(choice != 0);
}

// ---------------------- CODE MODE SELECTOR ----------------------
void codeModeSelector() {
    while (true) {
        system("cls");
        drawTitleBox("CODE IMPLEMENTATION MODE - Choose Implementation");
        setColor(10);
        cout << "\nChoose Implementation:\n";
        cout << "1. Array Implementation\n";
        cout << "2. Linked List Implementation\n";
        cout << "3. Queue Token System\n"; 
        cout << "4. Stack\n";
        cout << "0. Back\n";
        setColor(7);

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
             codeMode(); // Array code mode
        }
        else if (choice == 2) {
            int llChoice;
            do {
                system("cls");
                drawTitleBox("LINKED LIST TYPE SELECTION (Business Accounts)");
                setColor(10);
                cout << "\n1. Singly Linked List (SLL)";
                cout << "\n2. Doubly Linked List (DLL)";
                cout<<"\n3. Circular linklist(CLL)";
                cout << "\n0. Back\n";
                setColor(7);
                cout << "Enter your choice: ";
                cin >> llChoice;

                if (llChoice == 1) {
                     linkedListCodeMode();
                }
                else if (llChoice == 2) {
                     doublyLinkedListCodeMode();
                }
                else if (llChoice == 3) {
                     CircBankSystemMenu();

                }
                else if (llChoice == 0) break;
                else {
                    setColor(12);
                    cout << "Invalid choice.\n";
                    setColor(7);
                    pauseAndWait();
                }
            } while (llChoice != 0);
        }
        else if (choice == 3) {
             runBankQueueSystem();
        }
        else if (choice == 4) {
            runStackSystem();   // Stack system
        }
        else if (choice == 0) break;
        else {
            setColor(12);
            cout << "Invalid choice.\n";
            setColor(7);
            pauseAndWait();
        }
    }
}


// ---------------------- WELCOME & MAIN (modified to call codeModeSelector) ----------------------

void welcomePage(int &viewMode) {
    system("cls");
    drawTitleBox("WELCOME TO DSA BANK MANAGEMENT SYSTEM");
    setColor(11);
    cout << "\nThis program demonstrates:\n";
    cout << "- Array operations on bank customer data (dynamic array implementation)\n";
    cout << "- Algorithm Mode with data-structure specific bank algorithms\n";
    cout << "- Code Mode with 30 hardcoded customers and full CRUD & transactions\n\n";
    setColor(12);
    cout << "Choose how you want to learn:\n";
    setColor(10);
    cout << "1. Algorithm Steps (Conceptual Explanation)\n";
    cout << "2. Code Implementation (Interactive C++ Mode)\n\n";
    setColor(14);
    cout << "Enter your choice (1 or 2): ";
    setColor(7);
    cin >> viewMode;
    if (viewMode != 1 && viewMode != 2) {
        setColor(12);
        cout << "Invalid choice. Defaulting to Algorithm mode.\n";
        setColor(7);
        viewMode = 1;
        pauseAndWait();
    }
}

int main() {
    SetConsoleTitle("DSA Bank Management System - Combined Version");
    int viewMode = 1;

    // initialize dynamic array
    initDynamicArrayFromHardcoded();

    while (true) {
        welcomePage(viewMode);

        if (viewMode == 1) {
            algorithmMode();
            system("cls");
            drawTitleBox("RETURNING FROM ALGORITHM MODE");
            setColor(10);
            cout << "\n1) Return to Welcome Page\n2) Exit\n";
            setColor(7);
            cout << "Choice: ";
            int r;
			 cin >> r;
            if (r == 2) break;
            else continue;
        } else if (viewMode == 2) {
            codeModeSelector();
            system("cls");
            drawTitleBox("RETURNING FROM CODE MODE");
            setColor(10);
            cout << "\n1) Return to Welcome Page\n2) Exit\n";
            setColor(7);
            cout << "Choice: ";
            int r; 
			cin >> r;
            if (r == 2) break;
            else continue;
        } else {
            setColor(12);
            cout << "Unexpected mode. Exiting.\n";
            setColor(7);
            break;
        }
    }

    // cleanup
    delete [] dynArr;
    // cleanup linked list if any
    while (headLL) { LLNode* t = headLL; headLL = headLL->next; delete t; }

    system("cls");
    drawTitleBox("THANK YOU - DSA BANK MANAGEMENT SYSTEM");
    setColor(10);
    cout << "\nExiting program. Goodbye!\n\n";
    setColor(7);
    return 0;
}
