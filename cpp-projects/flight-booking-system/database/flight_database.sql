-- 延迟所有约束
SET CONSTRAINTS ALL DEFERRED;
-- ----------------------------
-- 表结构: admin_info
-- ----------------------------
DROP TABLE IF EXISTS admin_info;
CREATE TABLE admin_info (
    admin_id VARCHAR(255) PRIMARY KEY,
    admin_pwd VARCHAR(255) NOT NULL
);
-- 插入数据: admin_info
INSERT INTO admin_info (admin_id, admin_pwd)
VALUES ('114', '514'),
    ('233', '666');
-- ----------------------------
-- 表结构: user_info
-- ----------------------------
DROP TABLE IF EXISTS user_info;
CREATE TABLE user_info (
    u_name VARCHAR(255) NOT NULL,
    -- 用户名，不为空
    u_IDCard VARCHAR(255) NOT NULL,
    -- 用户身份证号，不为空
    u_tel VARCHAR(255) PRIMARY KEY,
    -- 用户电话，主键
    u_pwd VARCHAR(255) NOT NULL -- 用户密码，不为空
);
-- 插入数据: user_info
INSERT INTO user_info (u_name, u_IDCard, u_tel, u_pwd)
VALUES (
        '陈超成',
        '440524199012123456',
        '12345678901',
        '123456'
    ),
    (
        '黄诗盈',
        '440524199112123456',
        '12345678902',
        '123456'
    ),
    (
        '梁君豪',
        '440524199212123456',
        '12345678903',
        '123456'
    ),
    (
        '李怡欣',
        '440524199312123456',
        '12345678904',
        '123456'
    );
-- ----------------------------
-- 表结构: flight_info
-- ----------------------------
DROP TABLE IF EXISTS flight_info;
CREATE TABLE flight_info (
    f_num VARCHAR(255) PRIMARY KEY,
    -- 航班号，主键
    f_price DOUBLE PRECISION NOT NULL,
    -- 价格，不为空
    f_dep_date DATE NOT NULL,
    -- 起飞日期，不为空
    f_arr_date DATE NOT NULL,
    -- 到达日期，不为空
    f_dep_time TIME NOT NULL,
    -- 起飞时间，不为空
    f_dis DOUBLE PRECISION NOT NULL,
    -- 距离，不为空
    f_type VARCHAR(255) NOT NULL,
    -- 飞机类型，不为空
    f_cro_city VARCHAR(255),
    -- 中转城市，可为空
    f_dep_city VARCHAR(255) NOT NULL,
    -- 起飞城市，不为空
    f_arr_city VARCHAR(255) NOT NULL -- 到达城市，不为空
);
-- 插入数据: flight_info
INSERT INTO flight_info (
        f_num,
        f_price,
        f_dep_date,
        f_arr_date,
        f_dep_time,
        f_dis,
        f_type,
        f_cro_city,
        f_dep_city,
        f_arr_city
    )
VALUES (
        'BJ-GZ123',
        1200,
        '2024-07-21',
        '2024-07-21',
        '09:11:49',
        1883,
        '空客320',
        '福州',
        '北京',
        '广州'
    ),
    (
        'GZ-BJ123',
        756,
        '2024-07-24',
        '2024-07-24',
        '16:11:52',
        1883,
        '波音747',
        '济南',
        '广州',
        '北京'
    ),
    (
        'GZ-SH123',
        654,
        '2024-07-23',
        '2024-07-23',
        '11:59:09',
        1210,
        '空客321',
        '武汉',
        '广州',
        '上海'
    ),
    (
        'GZ-SZ156',
        678,
        '2024-07-26',
        '2024-07-26',
        '09:11:58',
        120,
        '波音747',
        NULL,
        '广州',
        '深圳'
    ),
    (
        'SZ-CD145',
        985,
        '2024-07-27',
        '2024-07-27',
        '20:12:04',
        1320,
        '波音777',
        NULL,
        '深圳',
        '成都'
    );
-- ----------------------------
-- 表结构: order_info
-- ----------------------------
DROP TABLE IF EXISTS order_info;
CREATE TABLE order_info (
    order_num VARCHAR(255) PRIMARY KEY,
    -- 订单号，主键
    order_flight_num VARCHAR(255),
    -- 订单航班号
    order_u_tel VARCHAR(255) NOT NULL,
    -- 订单用户电话，不为空
    order_u_name VARCHAR(255),
    -- 订单用户名
    order_pay_state VARCHAR(255) NOT NULL,
    -- 支付状态，不为空
    order_flight_date DATE,
    -- 航班日期
    order_flight_time TIME,
    -- 航班时间
    order_flight_dep_city VARCHAR(255),
    -- 起飞城市
    order_flight_arr_city VARCHAR(255),
    -- 到达城市
    order_flight_price DOUBLE PRECISION,
    -- 航班价格
    order_time TIME,
    -- 订单时间
    order_pay_time TIME,
    -- 支付时间
    CONSTRAINT fk_flight_num FOREIGN KEY (order_flight_num) REFERENCES flight_info (f_num),
    -- 外键，关联flight_info表
    CONSTRAINT fk_u_tel FOREIGN KEY (order_u_tel) REFERENCES user_info (u_tel) -- 外键，关联user_info表
);
-- 插入数据: order_info
INSERT INTO order_info (
        order_num,
        order_flight_num,
        order_u_tel,
        order_u_name,
        order_pay_state,
        order_flight_date,
        order_flight_time,
        order_flight_dep_city,
        order_flight_arr_city,
        order_flight_price,
        order_time,
        order_pay_time
    )
VALUES (
        '1234567890120240724161152',
        'GZ-BJ123',
        '12345678901',
        '陈超成',
        '已支付',
        '2024-07-24',
        '16:11:52',
        '广州',
        '北京',
        756,
        '16:11:52',
        '16:20:49'
    ),
    (
        '1234567890220240724161153',
        'GZ-BJ123',
        '12345678902',
        '黄诗盈',
        '已支付',
        '2024-07-24',
        '16:11:52',
        '广州',
        '北京',
        756,
        '16:11:53',
        '16:21:17'
    ),
    (
        '1234567890320240724161154',
        'GZ-BJ123',
        '12345678903',
        '梁君豪',
        '已支付',
        '2024-07-24',
        '16:11:52',
        '广州',
        '北京',
        756,
        '16:11:54',
        '16:22:06'
    ),
    (
        '1234567890420240726091158',
        'GZ-SZ156',
        '12345678904',
        '李怡欣',
        '未支付',
        '2024-07-26',
        '09:11:58',
        '广州',
        '深圳',
        678,
        '09:11:58',
        NULL
    );
-- ----------------------------
-- 表结构: ele_ticket
-- ----------------------------
DROP TABLE IF EXISTS ele_ticket;
CREATE TABLE ele_ticket (
    e_ticket_num VARCHAR(255) PRIMARY KEY,
    -- 电子票号，主键
    e_order_num VARCHAR(255),
    -- 订单号
    e_ticket_u_name VARCHAR(255),
    -- 票用户名
    e_flight_num VARCHAR(255),
    -- 航班号
    e_flight_dep_city VARCHAR(255),
    -- 起飞城市
    e_flight_arr_city VARCHAR(255),
    -- 到达城市
    e_flight_date DATE,
    -- 航班日期
    e_flight_dep_time TIME,
    -- 起飞时间
    e_flight_price DOUBLE PRECISION DEFAULT 0,
    -- 航班价格，默认0
    CONSTRAINT fk_e_order_num FOREIGN KEY (e_order_num) REFERENCES order_info (order_num),
    -- 外键，关联order_info表
    CONSTRAINT fk_e_flight_num FOREIGN KEY (e_flight_num) REFERENCES flight_info (f_num) -- 外键，关联flight_info表
);
-- 插入数据: ele_ticket
INSERT INTO ele_ticket (
        e_ticket_num,
        e_order_num,
        e_ticket_u_name,
        e_flight_num,
        e_flight_dep_city,
        e_flight_arr_city,
        e_flight_date,
        e_flight_dep_time,
        e_flight_price
    )
VALUES (
        'GZ-BJ12320240724161152',
        '12320240724161152',
        '陈超成',
        'GZ-BJ123',
        '广州',
        '北京',
        '2024-07-24',
        '16:11:52',
        756
    ),
    (
        'GZ-BJ12320240724161153',
        '12320240724161153',
        '黄诗盈',
        'GZ-BJ123',
        '广州',
        '北京',
        '2024-07-24',
        '16:11:52',
        756
    ),
    (
        'GZ-BJ12320240724161154',
        '12320240724161154',
        '梁君豪',
        'GZ-BJ123',
        '广州',
        '北京',
        '2024-07-24',
        '16:11:52',
        756
    ),
    (
        'GZ-SZ15620240726091158',
        '12320240726091158',
        '李怡欣',
        'GZ-SZ156',
        '广州',
        '深圳',
        '2024-07-26',
        '09:11:58',
        678
    );
-- ----------------------------
-- 表结构: flight_com_info
-- ----------------------------
DROP TABLE IF EXISTS flight_com_info;
CREATE TABLE flight_com_info (
    f_com_num VARCHAR(255) PRIMARY KEY,
    -- 公司号，主键
    f_com_name VARCHAR(255) NOT NULL,
    -- 公司名称，不为空
    f_com_addr VARCHAR(255) NOT NULL,
    -- 公司地址，不为空
    f_com_tel VARCHAR(255) NOT NULL,
    -- 公司电话，不为空
    f_com_wechat VARCHAR(255) NOT NULL -- 公司微信，不为空
);
-- 插入数据: flight_com_info
INSERT INTO flight_com_info (
        f_com_num,
        f_com_name,
        f_com_addr,
        f_com_tel,
        f_com_wechat
    )
VALUES ('01', '中国国际航空', '北京', '010-12345678', 'ICACAO'),
    ('02', '广州国际航空', '广州', '020-12345678', 'HNA'),
    ('03', '深圳航空公司', '深圳', '0755-12345678', 'DTT'),
    ('04', '厦门航空公司', '厦门', '0592-12345678', 'XMA'),
    ('05', '四川航空公司', '成都', '028-12345678', 'CHN');
-- 恢复所有约束
SET CONSTRAINTS ALL IMMEDIATE;