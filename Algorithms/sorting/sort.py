import hypothesis.strategies as st

def bubble_sort(data):

    n = len(data)
  
    for i in range(n-1):
        yield 'label', 'Find Smallest'
  
        for j in range(0, n-i-1):

            yield 'focus', j+1
            
            yield 'cmp', j, j+1

            if data[j] > data[j+1] :
                data[j], data[j+1] = data[j+1], data[j]

                yield 'label', 'Move to Front'
                yield 'swap', j+1, j

    

def selection_sort(data):
    """
    Sort contents of data in place.
    This is a generator which yields each algorithm step (comparison or
    swap), allow for visualization or instrumentation. The caller is
    responsible for performing swaps.
    """
    for dest in range(len(data) - 1):
        yield 'label', 'Find Smallest'
        smallest_i = dest
        yield 'focus', dest
        for i in range(dest + 1, len(data)):
            yield 'cmp', smallest_i, i
            if data[i] < data[smallest_i]:
                smallest_i = i
                yield 'focus', i
        yield 'label', 'Move to Front'
        yield 'swap', dest, smallest_i


def merge(data, left, mid, right):
    """
    Copy each sub-list, reverse them so we can pop from the end, and
    merge back into the main list. This isn't terribly efficient but
    it's convenient.
    """
    yield 'merge', (left, mid), (mid, right)
    sub_left = data[left:mid]
    sub_right = data[mid:right]
    for i in range(left, right):
        if not sub_right or (sub_left and sub_left[0] < sub_right[0]):
            yield 'set', i, sub_left[0]
            del sub_left[0]
        else:
            yield 'set', i, sub_right[0]
            del sub_right[0]
    assert len(sub_left) == 0
    assert len(sub_right) == 0


def merge_sort(data, left=None, right=None):
    """Merge sort in place. Like selection_sort, this is a generator."""
    if left is None:
        left = 0
    if right is None:
        right = len(data)
    if right <= left + 1:
        return

    mid = (left + right) // 2
    yield 'subdivide', left, mid
    yield from merge_sort(data, left, mid)
    yield 'subdivide', mid + 1, right
    yield from merge_sort(data, mid, right)
    yield from merge(data, left, mid, right)


def quicksort(data, left=None, right=None):
    """Quick sort in place. Like selection_sort, this is a generator."""
    if left is None:
        left = 0
    if right is None:
        right = len(data) - 1
    if right <= left:
        return

    mid = None
    def partition(data, left, right):
        pi = (left + right) // 2
        pivot = data[pi]
        yield 'label', 'Partition, pivot=%s' % pivot
        i = left
        j = right
        while True:
            yield 'focus', pi
            while True:
                yield 'cmp', i, pi
                if i == pi or data[i] > pivot:
                    yield 'focus', i, pi
                    break
                i += 1
            while True:
                yield 'cmp', j, pi
                if j == pi or data[j] < pivot:
                    yield 'focus', i, j
                    break
                j -= 1

            nonlocal mid
            if i >= j:
                mid = j
                return
            elif data[i] == pivot and data[j] == pivot:
                mid = i
                return

            yield 'swap', i, j
            if i == pi:
                pi = j
            elif j == pi:
                pi = i

    yield from partition(data, left, right)
    assert(mid is not None)

    yield 'label', 'Sort Left Side'
    yield 'subdivide', left, mid + 1
    yield from quicksort(data, left, mid)
    yield 'label', 'Sort Right Side'
    yield 'subdivide', mid + 1, right + 1
    yield from quicksort(data, mid + 1, right)
    yield 'subdivide', left, right + 1
    yield 'label', 'Sorted from %d to %d' % (left, right)



def heapify(arr, n, i):
    """
    To heapify subtree rooted at index i. n is size of heap
    """
    yield 'label', 'Heapified'

    largest = i # Initialize largest as root
    l = 2 * i + 1     # left = 2*i + 1
    r = 2 * i + 2     # right = 2*i + 2

    # See if left child of root exists and is
    # greater than root
    if l < n and arr[i] < arr[l]:
        largest = l

    # See if right child of root exists and is
    # greater than root
    if r < n and arr[largest] < arr[r]:
        largest = r

    # Change root, if needed
    if largest != i:
        arr[i],arr[largest] = arr[largest],arr[i] # swap
        yield 'swap', i, largest

        # Heapify the root.
        heapify(arr, n, largest)

def heap_sort(arr):
    """
    The main function to sort an array of given size
    """
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # One by one extract elements
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i] # swap
        yield 'swap', i, 0
        heapify(arr, i, 0)    
    
def perform_effect(effect, data):
    """Apply an effect to a list, modifying the data argument."""
    kind = effect[0]
    if kind == 'swap':
        a, b = effect[1:]
        data[a], data[b] = data[b], data[a]
    if kind == 'set':
        a, b = effect[1:]
        data[a] = b


def run(sort, data, callback=None):
    """Run a sorting algorithm, passing all effects to optional callback."""
    for effect in sort(data):
        if callback:
            callback(*effect)
        perform_effect(effect, data)


def print_effects(sort, data):
    """Run a sorting algorithm, printing all steps."""
    run(sort, data, lambda *e: print(*e))


def count_steps(sort, data):
    """Run a sorting algorithm, returning the number of effects performed."""

    def inc_count(effect, *args):
        nonlocal count
        if effect in ['cmp', 'swap', 'set']:
            count = count + 1
    count = 0

    run(sort, data, inc_count)
    return count


def random_list(length, max_value=None):
    return st.lists(st.integers(min_value=1, max_value=max_value),
                    min_size=length, max_size=length).example()


if __name__ == '__main__':
    lst = [-2, -2]
    mysort = quicksort

    print_effects(mysort, lst)
    print(lst)
    print(count_steps(mysort, lst), 'steps')
