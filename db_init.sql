create table auth (
    account text primary key not null,
    password text not null
)

-- 下方插入管理员账户与密码
insert into auth values ('manager_test', '1234567')