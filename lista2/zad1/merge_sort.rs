use std::io;

fn merge(first: &[u32], second: &[u32], comparisons: &mut u32, replacements: &mut u32) -> Vec<u32> {

    // create new vector

    let mut merged = Vec::new();
    let mut idx_f = 0;
    let mut idx_s = 0;

    // merge

    while idx_f < first.len() && idx_s < second.len() {
        if first[idx_f] <= second[idx_s] {
            merged.push(first[idx_f]);
            idx_f += 1;
        } else {
            merged.push(second[idx_s]);
            idx_s += 1;
        }
        
        *comparisons += 1;
        *replacements += 1;
    }

    // push the remaining elements
    
    for i in idx_f..first.len() {
        merged.push(first[i]);
        *replacements += 1;
    }
    
    for i in idx_s..second.len() {
        merged.push(second[i]);
        *replacements += 1;
    }

    merged
}

fn merge_sort(array: &[u32], n: usize, comparisons: &mut u32, replacements: &mut u32) -> Vec<u32> {

    if array.len() == 1 {
       return array.to_vec();
    }

    // divide array into two and mergesort

    let first = merge_sort(&array[0..array.len() / 2], n, comparisons, replacements);
    let second = merge_sort(&array[array.len() / 2..array.len()], n, comparisons, replacements);

    // merge the results

    let merged = merge(&first[..], &second[..], comparisons, replacements);

    // output merged halfs

    if n < 40 {
        print!("first: {:02?}  +", first);
        print!("  second: {:02?}", second);
        println!("  ---->  merged into: {:02?}", merged);
    }

    merged
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

    let mut comparisons: u32 = 0;
    let mut replacements: u32 = 0;

    // pre-sorted output
    
    if n < 40 {
        println!("input array: {:02?}", numbers);
    }

    // sort the numbers

    numbers = merge_sort(&numbers, numbers.len(), &mut comparisons, &mut replacements);

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
