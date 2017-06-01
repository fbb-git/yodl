typedef struct StrVectorPair
{
    char *d_key;
    char *d_value;
} StrVectorPair;

typedef struct StrVector
{
    size_t d_capacity;
    size_t d_size;
    StrVectorPair **d_pair;
} StrVector;

void strVector_construct(StrVector *strVector);
void strVector_destruct(StrVector *strVector);

void strVector_add(StrVector *sv, char const *key, char const *value);
int strVector_find(StrVector const *sv, char const *key);

static inline StrVectorPair const *strVector_index(
                                        StrVector const *sv, size_t idx)
{
    return sv->d_pair[idx];
}


