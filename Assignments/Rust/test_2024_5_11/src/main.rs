fn bubble_sort<T: Ord>(arr: &mut [T]) {
    let len: usize = arr.len();
    for i in 0..(len - 1) {
        for j in 0..(len - 1 - i) {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
            }
        }
    }
}

fn main() {
    let mut arr: [i32; 7] = [64, 34, 25, 12, 22, 11, 90];
    println!("Original array: {:?}", arr);

    bubble_sort(&mut arr);

    println!("Sorted array: {:?}", arr);

    let mut arr_str: [&str; 5] = ["rust", "java", "python", "c", "javascript"];
    println!("Original array: {:?}", arr_str);

    bubble_sort(&mut arr_str);

    println!("Sorted array: {:?}", arr_str);
}
