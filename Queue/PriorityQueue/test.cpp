#include <bits/stdc++.h>
#include "PriorityQueue_by_Heap.hpp"

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PriorityQueue<char>* pq = new PriorityQueue<char>(HeapType::MIN);
    pq->Insert(9, 'A');
    pq->Insert(7, 'B');
    pq->Insert(6, 'C');
    pq->Insert(5, 'D');
    pq->Insert(4, 'E');
    pq->Insert(5, 'F');
    pq->Insert(3, 'G');
    pq->Insert(2, 'H');
    pq->Insert(1, 'I');
    pq->Insert(3, 'J');
    pq->Insert(2, 'K');

    pq->printInfo();
    cout << "------------------------------------------" << ENDL;

    auto pop = pq->Delete();
    cout << "Pop : (" << pop.getKey() << "," << pop.getValue() << ")" << ENDL;

    auto top = pq->Top();
    cout << "Top : (" << top.getKey() << "," << top.getValue() << ")" << ENDL;

    pq->printInfo();

    delete pq;

    return 0;
}