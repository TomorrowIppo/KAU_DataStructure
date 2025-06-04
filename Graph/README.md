# Graph Algorithms Project

이 프로젝트는 다양한 그래프 표현 방식 및 알고리즘 구현을 목표로 합니다.  
학습 목적에 따라 C++로 자료구조를 직접 구현하며, 객체지향 원칙과 테스트 기반 개발 방식을 지향합니다.

---

## 📌 브랜치 전략

- `main`: 안정화된 코드만 머지되는 최종 브랜치입니다.
- `develop`: 기능 개발 및 통합 테스트가 이루어지는 브랜치입니다.
- `feature/*`: 개별 기능 개발을 위한 브랜치입니다. ex) `feature/kruskal`, `feature/avl`

---

## ✅ 구현 내용

### 공통 인터페이스
- `IGraph`: 그래프 클래스의 추상 기반 인터페이스
  - 공통 메서드: `insertVertex`, `insertEdge`, `deleteVertex`, `deleteEdge`, `getAdjacency`, `getVertices`, `getWeight`, `isDirected` 등

### 그래프 구현체
- `AdjacencyList`  
  - 연결 리스트 기반 인접 리스트 구현  
  - `dir` 플래그를 통한 방향/무방향 그래프 설정
- `AdjacencyMatrix`  
  - 2차원 배열 기반 인접 행렬 구현  
  - `dir` 플래그를 통한 방향/무방향 그래프 설정
- 각 클래스의 `printGraph()`는 그래프 이름태그([AdjList], [AdjMatrix])를 출력에 포함하여 가독성 향상

### MST 및 알고리즘
- `kruskal.hpp`: 크루스칼 최소 신장 트리 알고리즘 구현
  - `std::tuple` 기반 엣지 리스트 생성
  - 유니온 파인드로 사이클 방지
  - 방향 그래프에서도 u < v 조건으로 중복 제거

---

## 🔧 테스트

각 구현체 및 알고리즘에 대한 개별 테스트 코드 존재  
모든 `test.cpp`는 로컬 환경에서 실행 확인됨

---

## 📝 TODO

- `Prim` 알고리즘 추가 구현
- `Dijkstra` 알고리즘 추가 구현
