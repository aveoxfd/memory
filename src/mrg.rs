//merge blocks

struct BlockHeader {
    size: i64,
    flag: i8,
    next: *mut BlockHeader,
}

struct GenMng {
    list: BlockHeader,
}

fn merge_blocks(list: *mut GenMng) {

}