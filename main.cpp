//
// Created by 이인성 on 2021/07/25.
//

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
unsigned int INF = -1;

vector<vector<unsigned int>> matrix;
vector<bool> visit;
vector<unsigned int> min_distance;

int getSmallIndex(int node) {
  int min = INF;
  int index = 0;
  for(int i=0; i<node; i++) {
    if(min_distance[i] < min && !visit[i]) {
      min = min_distance[i];
      index = i;
    }
  }
  return index;
}

void dijkstra(int start, int node) {
  for(int i=0; i<node; i++) {
    min_distance[i] = matrix[start][i];
  }
  visit[start] = true;
  for(int i=0; i<node-2; i++) {
    int current = getSmallIndex(node);
    visit[current] = true;
    for(int j=0; j<node; j++) {
      if(!visit[j]) {
        if(min_distance[current] + matrix[current][j] < min_distance[j]) {
          min_distance[j] = min_distance[current] + matrix[current][j];
        }
      }
    }
  }
}

int main() {
  vector<int> result;
  int N, M, X;
  int result_max = 0;
  cin >> N >> M >> X;
  matrix.resize(N);
  visit.resize(N);
  min_distance.resize(N);
  result.resize(N);
  for(int i=0; i<N; i++)
    matrix[i].resize(N, -1);
  for(int i=0; i<M; i++) {
    int idx_i, idx_j, cost;
    scanf("%d%d%d", &idx_i, &idx_j, &cost);
    matrix[idx_i-1][idx_j-1] = cost;
  }
  for(int i=0; i<N; i++) {
    matrix[i][i] = 0;
  }
  dijkstra(X, N);
  for(int i=0; i<N; i++) {
    result[i] = min_distance[i];
  }
  for(int i=0; i<N; i++) {
    visit[i] = false;
  }
  for(int i=0; i<N; i++) {
    dijkstra(i, N);
    result[i] += min_distance[X];
    if(result_max < result[i]) {
      result_max = result[i];
    }
    for(int i=0; i<N; i++) {
      visit[i] = false;
    }
  }
  printf("%d\n", result_max);

  return 0;
}