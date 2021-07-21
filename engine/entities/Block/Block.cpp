#include "Block.h"

Block::Block(Vec cords, Vec size, int id, size_t type_num, float angle) : cords(cords), size(size), id(id), type_num(type_num),
                                                                          angle(angle) {}

EntityType Block::get_type() {
    return EntityType(ENTITY_NAME::WALL, type_num);
}

void Block::rotate(float add_angle) {
    angle += add_angle;
}

float Block::get_angle() const {
    return angle;
}

Vec Block::get_size() {
    return size;
}

Vec Block::get_cords() {
    return cords;
}

int Block::get_id() {
    return id;
}

bool check_blocks_intersection(Block* a, Block* b) {
    Vec cords1 = a->get_cords();
    Vec cords2 = b->get_cords();

    std::vector<Vec> points1(4,Vec(0,0)),points2(4,Vec(0,0));
    points1[0].x -= a->get_size().x/2;
    points1[1].x -= a->get_size().x/2;
    points1[2].x += a->get_size().x/2;
    points1[3].x += a->get_size().x/2;

    points1[0].y += a->get_size().y/2;
    points1[1].y -= a->get_size().y/2;
    points1[2].y -= a->get_size().y/2;
    points1[3].y += a->get_size().y/2;

    points2[0].x -= b->get_size().x/2;
    points2[1].x -= b->get_size().x/2;
    points2[2].x += b->get_size().x/2;
    points2[3].x += b->get_size().x/2;

    points2[0].y += b->get_size().y/2;
    points2[1].y -= b->get_size().y/2;
    points2[2].y -= b->get_size().y/2;
    points2[3].y += b->get_size().y/2;

    for(auto &el : points1) {
        rotate_vec(el, a->get_angle());
        el+=cords1;
    }
    for(auto &el : points2) {
        rotate_vec(el, b->get_angle());
        el+=cords2;
    }

    bool ret_value = false;
    for(int i=0;i<4;++i) {
        Vec p1 =  points1[i];
        Vec p2 =  points1[(i+1)%4];
        for(int j=0;j<4;++j) {
            Vec p3 =  points2[j];
            Vec p4 =  points2[(j+1)%4];

            if(get_segments_intersection(p1,p2,p3,p4) != Vec(-1000,-1000)) {
                ret_value = true;
                goto skip;
            }
        }
    }
    skip:;
    return ret_value;
}