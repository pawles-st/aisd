use std::io;

fn insertion_sort(array: &mut Vec<u32>) {

    let mut comparisons = 0;
    let mut replacements = 0;

    for i in 1..=array.len() - 1 {

        // currently sorted element

        let key = array[i];

        // find insertion point

        let mut j = (i - 1) as i64;
        while j >= 0 && array[j as usize] > key {
            j -= 1;
            comparisons += 1;
        }

        if j >= 0 {
            comparisons += 1;
        }

        // rotate the relevant slice

        array[(j+1) as usize..=i].rotate_right(1);
        replacements += i as i64 - j;

        // output current state of the vector

        if array.len() < 40 {
            println!("after {:02} insert(s): {:02?}", i, array);
        }
    }

    println!("comparisons: {comparisons}");
    println!("replacements: {replacements}");
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

    // pre-sorted output
    
    if n < 40 {
        println!("input array: {:02?}", numbers);
    }

    // sort the numbers

    insertion_sort(&mut numbers);

    // verify sortedness
    
    if numbers.len() > 1 {
        for i in 0..numbers.len() - 2 {
            assert!(numbers[i] <= numbers[i + 1]);
        }
    }

    // post-sorted output

    if n < 40 {
        println!("sorted: {:02?}", numbers);
    }

    Ok(())
}
