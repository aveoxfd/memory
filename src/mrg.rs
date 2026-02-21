//merge blocks

#[repr(C)] //tells the compiler to use c-style struct layout
struct BlockHeader {
    size: i64,
    flag: i8,
    next: *mut BlockHeader,
}

fn merge_blocks(list : *mut BlockHeader) {
    unsafe{
        let mut current : *mut BlockHeader = list;
        while !current.next{
            
        }
    }
}