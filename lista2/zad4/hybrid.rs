use std::io;

fn insertion_sort(array: &mut [u32], n: usize, comparisons: &mut u64, replacements: &mut u64) {

    for i in 1..=array.len() - 1 {

        // currently sorted element

        let key = array[i];

        // find insertion point

        let mut j = (i - 1) as i64;
        while j >= 0 && array[j as usize] > key {
            j -= 1;
            *comparisons += 1;
        }

        if j >= 0 {
            *comparisons += 1;
        }

        // rotate the relevant slice

        array[(j+1) as usize..=i].rotate_right(1);
        *replacements += (i as i64 - j) as u64;

        // output current state of the vector

        if n < 40 {
            println!("after {:02} insert(s): {:02?}", i, array);
        }
    }
}

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

fn hybrid_sort(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) {
    if right > left {

        if right - left > 10 { // quicksort
            // perform hoare partition

            let mid = partition(array, left, right, comparisons, replacements);
            
            // output partiton effect

            if array.len() < 40 {
                print!("pivot: {:02} --->", array[(left + right) / 2]);
                //println!(" {:02?}", array);
                if left <= mid {
                    print!(" left: {:02?}, ", &array[left..=mid]);
                }
                if mid + 1 <= right {
                    println!("right: {:02?}", &array[(mid + 1)..=right]);
                }
            }

            // recursively quicksort

            if left <= mid {
                hybrid_sort(array, left, mid, comparisons, replacements);
            }
            if mid + 1 <= right {
                hybrid_sort(array, mid + 1, right, comparisons, replacements);
            }
        } else { // insertion sort
            let n = array.len();
            insertion_sort(&mut array[left..=right], n, comparisons, replacements);
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
    hybrid_sort(&mut numbers, 0, r, &mut comparisons, &mut replacements);

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
