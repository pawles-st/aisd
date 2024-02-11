use std::io;

fn partition(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) -> usize {
    let pivot = array[(left + right) / 2];
    let mut i = left as isize - 1;
    let mut j = right + 1;
    loop {

        // find next incorrect element from left

        loop {
            i += 1;
            *comparisons += 1;
            if array[i as usize] >= pivot {
                break;
            }
        }

        // find next incorrect element from right
        
        loop {
            j -= 1;
            *comparisons += 1;
            if array[j] <= pivot {
                break;
            }
        }

        // if scanned the entire array. return right index

        if i >= j as isize {
            return j;
        }

        // swap the incorrect elements

        *replacements += 3;
        array.swap(i as usize, j);
    }
}

fn quick_sort(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) {
    if right > left {
        
        if array.len() < 40 {
            print!("pivot: {:02} --->", array[(left + right) / 2]);
        }

        // perform hoare partition

        let mid = partition(array, left, right, comparisons, replacements);
        
        // output partiton effect

        if array.len() < 40 {
            if left <= mid {
                print!(" left: {:02?}, ", &array[left..=mid]);
            }
            if mid + 1 <= right {
                println!("right: {:02?}", &array[(mid + 1)..=right]);
            }
        }

        // recursively quicksort

        if left <= mid {
            quick_sort(array, left, mid, comparisons, replacements);
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
    quick_sort(&mut numbers, 0, r, &mut comparisons, &mut replacements);

    // verify sortedness
    
    if numbers.len() > 1 {
        for i in 0..numbers.len() - 2 {
            assert!(numbers[i] <= numbers[i + 1]);
        }
    }

    // post-sorted output

    println!("comparisons: {}", comparisons);
    println!("replacements: {}", replacements);

    if n < 40 {
        println!("sorted: {:02?}", numbers);
    }

    Ok(())
}
