vector <mint>* gauss(vector <vector <mint>> a) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector <int> pivot(m, -1);

	for (int col = 0, row = 0; col < m and row < n; col++) {
		int cur = row;
		for (int i = row; i < n; i++)
			if (ABS(a[i][col]) > ABS(a[cur][col]))
				cur = i;
		if (a[cur][col] == 0)
			continue;
		for (int i = col; i <= m; i++)
			swap(a[cur][i], a[row][i]);
		pivot[col] = row;

		for (int i = 0; i < n; i++) if (i != row) {
			if (a[i][col] == 0)
				continue;
			mint c = a[i][col] / a[row][col];
			for (int j = col; j <= m; j++)
				a[i][j] -= a[row][j] * c;
		}
		row++;
	}

	vector <mint> *ans = new vector <mint> (m, 0);
	for (int i = 0; i < m; i++) if (pivot[i] != -1)
		(*ans)[i] = a[pivot[i]][m] / a[pivot[i]][i];
	for (int i = 0; i < n; i++) {
		mint s = a[i][m];
		for (int j = 0; j < m; j++)
			s -= (*ans)[j] * a[i][j];
		if (s)
			return nullptr;
	}

	return ans;
}