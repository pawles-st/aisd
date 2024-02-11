use std::io;
use std::time::Instant;

fn partition(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) -> (usize, usize) {

    // make sure left value < right value

    *comparisons += 1;
    if array[left] > array[right] {
        array.swap(left, right);
        *replacements += 3;
    }

    // pivots

    let p = array[left];
    let q = array[right];

    // count elements
    
    let mut s = 0;
    let mut l = 0;

    // current left & right insertion points

    let mut i = left;
    let mut j = right;

    // current element

    let mut m = i + 1;

    while m < j {

        if l > s { // there's more larger elements
            *comparisons += 1;
            if array[m] >= q {
                l += 1;
                j -= 1;
                array.swap(m, j);
                *replacements += 3;
                m -= 1;
            } else {
                *comparisons += 1;
                if array[m] <= p {
                    s += 1;
                    i += 1;
                    array.swap(m, i);
                    *replacements += 3;
                }
            }
        } else { // there's more lesser elements
            *comparisons += 1;
            if array[m] <= p {
                s += 1;
                i += 1;
                array.swap(m, i);
                *replacements += 3;
            } else {
                *comparisons += 1;
                if array[m] >= q {
                    l += 1;
                    j -= 1;
                    array.swap(m, j);
                    *replacements += 3;
                    m -= 1;
                }
            }
        }
        
        m += 1;
    }
    array.swap(left, i);
    *replacements += 3;
    array.swap(right, j);
    *replacements += 3;

    (i, j)
}

fn dual_quick_sort(array: &mut [u32], left: usize, right: usize, comparisons: &mut u64, replacements: &mut u64) {
    if right > left {

        if array.len() < 40 {
            println!("sorting: {:02?}", &array[left..=right]);
            print!("pivots: {:02} {:02} ---> ", array[left], array[right]);
        }

        // perform partition

        let div = partition(array, left, right, comparisons, replacements);
        
        // output partiton effect

        if array.len() < 40 {
            if left < div.0 {
                print!("left: {:02?}, ", &array[left..div.0]);
            }
            if div.0 + 1 < div.1 {
                print!("middle: {:02?}, ", &array[(div.0 + 1)..div.1]);
            }
            if div.1 + 1 <= right {
                print!("right: {:02?}", &array[(div.1 + 1)..=right]);
            }
            println!();
        }

        // recursively dual quicksort

        if left < div.0 {
            dual_quick_sort(array, left, div.0 - 1, comparisons, replacements);
        }
        if div.0 + 1 < div.1 {
            dual_quick_sort(array, div.0 + 1, div.1 - 1, comparisons, replacements);
        }
        if div.1 + 1 <= right {
            dual_quick_sort(array, div.1 + 1, right, comparisons, replacements);
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
    dual_quick_sort(&mut numbers, 0, r, &mut comparisons, &mut replacements);
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
