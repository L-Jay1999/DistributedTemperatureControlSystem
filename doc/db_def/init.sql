create table slave.log (
    time integer not null,
    level integer not null,
    content text not null
);

create table master.log (
    time integer not null,
    level integer not null,
    content text not null
);

-- 认证用
create table master.user (
    room text not null,
    id text not null,
    use numeric not null default(0),
    cost numeric not null default(0),
    primary key (room, id)
);

create table master.auth (
    account text primary key not null,
    password text not null
)

create table master.room_power_stat (
    room text not null,
    is_start_up integer not null,
    time integer not null
)

create table master.room_request_stat (
    room text not null,
    initial_temperature numeric not null,
    target_temperature numeric not null,
    start_time integer not null,
    end_time integer not null,
    speed_level integer not null,
    cost numeric not null
)
