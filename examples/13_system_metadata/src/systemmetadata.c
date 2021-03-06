#include <include/systemmetadata.h>

typedef struct Position {
    int32_t x;
    int32_t y;
} Position;

typedef uint32_t Speed;

/* Display metadata that can be obtained from system callback */
void Metadata(EcsRows *rows) {
    void *row;

    printf("Running system '%s'\n", ecs_id(rows->world, rows->system));
    printf("delta_time = %f\n", rows->delta_time);

    int i;
    for (i = 0; i < rows->column_count; i ++) {
        EcsHandle component = ecs_handle(rows, i);
        printf("column %d: %s\n", i, ecs_id(rows->world, component));
    }

    for (row = rows->first; row < rows->last; row = ecs_next(rows, row)) {
        EcsHandle entity = ecs_entity(row);
        printf("process entity %lld\n", entity);
    }
}

int main(int argc, char *argv[]) {
    /* An EcsWorld contains all our entities, components and systems */
    EcsWorld *world = ecs_init();

    /* Register components and family */
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Speed);
    ECS_FAMILY(world, Object, Position, Speed);

    /* Register the Metadata system. */
    ECS_SYSTEM(world, Metadata, EcsOnFrame, Position, Speed);

    /* Create entity with Position and Speed */
    ecs_new(world, Object_h);

    /* Call ecs_progress */
    ecs_progress(world, 0.5);

    /* Cleanup the world. */
    return ecs_fini(world);
}
