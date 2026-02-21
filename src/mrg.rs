//merge blocks
/*
the block will be merged if:
-it has odd number of size;
-it less then  
*/

#[repr(C)] //tells the compiler to use c-style struct layout
struct BlockHeader {
    size: i64,
    flag: i8,
    next: *mut BlockHeader,
}

fn merge_blocks(list : *mut BlockHeader) {
    unsafe{
        let current : *mut BlockHeader = list;
        while !current.next{

            if current.size % 2 != 0

            current =  current.next;
        }
    }
}