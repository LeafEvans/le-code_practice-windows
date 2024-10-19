fn bubble_sort<T: Ord>(arr: &mut [T]) {
    let len = arr.len();
    for i in 0..(len - 1) {
        for j in 0..(len - 1 - i) {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
    }
}

fn main() {
    let mut arr = [67, 34, 25, 12, 22, 11, 90];
    println!("Original array: {:?}", arr);

    bubble_sort(&mut arr);
    println!("Sorted array: {:?}", arr);
}
