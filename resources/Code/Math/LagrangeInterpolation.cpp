Z lagrange(const std::vector <Z> &p, int x) {
    if (x < (int) p.size()) return p[x];

	  Z ans = 0, prod = 1;

	  for (int i = 1; i < (int) p.size(); i++) {
		    prod *= x - i;
		    prod /= -i;
	  }

	  for (int i = 0; i < (int) p.size(); i++) {
		    ans += prod * p[i];
		    if (i + 1 == (int) p.size()) break;
		    prod *= x - i;
		    prod /= x - (i + 1);
		    prod *= i - (int) p.size() + 1;
		    prod /= i + 1;
	  }
	  return ans;
}