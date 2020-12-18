function time_delay_loop()
{
    var loop_cnt = 1000;
    var set = {};
    for (var i = 0; i < loop_cnt; i++) {
        var obj = {id: i, attr: "attr"}
        set[i] = obj;
        for (var j = 0; j < i; j++) {
            set[j].id = j;
        }
    }
}

function test_leak()
{
    // test_array
    var array_a = [1, 2, 3, 4];  // leak

    // test closure
    function func1() {
        var obj = {"val": 1};
        function set(a) {
            obj.val = a;
        }
        function get() {
            return obj.val;
        }
        return {"set": set, "get": get};
    }
    
    var retobj = func1();
    retobj.set(10);
    // loop to trigger gc
    time_delay_loop();
}

test_leak();
