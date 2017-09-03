const int _PrimeSize = 28;
static const unsigned long _PrimeList [_PrimeSize] =
{
	53ul,         97ul,         193ul,       389ul,       769ul,
	1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
	49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
	1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
	50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

enum State
{
	EMPTY, EXIST, DELETE
};

static size_t BKDRHash(const char * str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str )
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

template<class K, class V>
struct HashNode
{
	pair<K, V>  _kv;
	State _s;

	HashNode()
		: _s(EMPTY)
	{}
};

// 2、size 素数
// 3、二次探测
template<class K, class V, class HashFun = _HashFun_<K>, bool IsLine = true>
class HashTable
{
	typedef HashTable<K, V, HashFun, IsLine> Self;
public:
	HashTable(size_t size = 10)
		: _size(0)
	{
		_tables.resize(GetNextPrime(size));
	}

	bool Insert(const K& key, const V& value);
	pair<HashNode<K, V>*, bool> Find(const K& key);
	bool Remove(const K& key);
private:
	void _CheckTable();
	void Swap(Self& ht);
	size_t _HashFunc(const K& key);
	size_t DetectedLine(size_t hashAddr);
	size_t Detected2(size_t hashAddr, size_t i);

protected:
	vector<HashNode<K,V>> _tables;
	size_t _size;    // 哈希表中有效数据的个数
};