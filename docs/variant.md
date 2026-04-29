- saves memory in stack based on the largest variant
- saves index to know which variant its pointing to at any point

- uses static_cast to cast from byte storage to void* and from that to T* for templates when needs to convert to type from index template I
    - uses template tables and uses variant index to reach the right implementation
- uses std::launder(interpret_cast<T*>(storage)) when T is given