use std::io;
use std::time::Instant;

fn partition(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) -> usize {

    // partition with respect to the first element

    let mut i = left;
    for j in left+1..=right {
        *comparisons += 1;
        if array[j] <= array[left] {
            i += 1;
            array.swap(i, j);
            *replacements += 3;
        }
    }
    array.swap(left, i);
    *replacements += 3;
    return i;
}

fn quick_sort(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) {
    if right > left {
        
        if array.len() < 40 {
            print!("pivot: {:02} --->", array[(left + right) / 2]);
        }

        // perform lomuto partition

        let mid = partition(array, left, right, comparisons, replacements);
        
        // output partiton effect

        if array.len() < 40 {
            print!(" {:02?}, ", &array[left..mid]);
            print!(" [{:02}], ", &array[mid]);
            println!("{:02?}", &array[(mid + 1)..=right]);
        }

        // recursively quicksort

        if left < mid {
            quick_sort(array, left, mid - 1, comparisons, replacements);
        }
        if mid + 1 <= right {
            quick_sort(array, mid + 1, right, comparisons, replacements);
        }
    }
}

fn main() -> io::Result<()> {

    // reading buffer

    let mut buf = String::new();

    // read number of elements
    
    io::stdin().read_line(&mut buf)?;
    let n: u32 = buf.trim().parse().unwrap();

    // read n numbers
    
    let mut numbers = Vec::new();
    
    for _ in 1..=n {
        buf.clear();
        io::stdin().read_line(&mut buf)?;
        let number: u32 = buf.trim().parse().unwrap();
        numbers.push(number);
    }

    let mut comparisons = 0;
    let mut replacements = 0;

    // pre-sorted output
    
    if n < 40 {
        println!("input array: {:02?}", numbers);
    }

    // sort the numbers

    let r = numbers.len() - 1;
    let start = Instant::now();
    quick_sort(&mut numbers, 0, r, &mut comparisons, &mut replacements);
    let end = Instant::now();
    let duration = end.checked_duration_since(start).unwrap();

    // verify sortedness
    
    if numbers.len() > 1 {
        for i in 0..numbers.len() - 2 {
            assert!(numbers[i] <= numbers[i + 1]);
        }
    }

    // post-sorted output

    println!("{} {} {}", comparisons, replacements, duration.as_nanos());

    if n < 40 {
        println!("sorted: {:02?}", numbers);
    }

    Ok(())
}
