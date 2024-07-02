#ifndef _PURITY_HPP
#define _PUTIRY_HPP

#include <math.h>
#include <vector>
#include <map>

using namespace std;

enum {
        ENTROPY = 1,
        GINI
};

template <typename T>
map<T, int> class_count(vector<T> x) {
        map<T, int> cc;
        for (T v : x) 
                if (cc.count(v) == 0)
                        // First time key is used
                        cc[v] = 1;
                else
                        // Key already exists
                        cc[v] += 1;
        return cc;
}

template <typename T>
double purity(vector<T> x, int measure) {
        map<T, int> counts = class_count(x);
        double accum = (measure == ENTROPY) ? 0 : 1;
        for (auto iter : counts) {
                double p = static_cast<double>(iter.second) / x.size();
                accum -= (measure == ENTROPY) ? (p * log(p)) : (p * p);
        }
        return accum;
}

/** Computes the Gini index for an integer class vector
 *      Gini index = 1 - \Sum p_i^2
 *  @param x : integer class vector
 *  @return Gini index
 */
template <typename T>
double entropy(vector<T> x) {
        return purity(x, ENTROPY);
}

/** Computes the entropy for an integer class vector
 *      entropy = - \Sum p_i * log (p_i)
 *  @param x : integer class vector
 *  @return entropy measurement
 */
template <typename T>
double gini_index(vector<T> x) {
        return purity<T>(x, GINI);
}

#endif // _PURITY_HPP
