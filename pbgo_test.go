package pbgo

import (
    "testing"
    "github.com/vcaesar/tt"
)

func TestBaseC(t *testing.T){
    go CallC()
    go CallC()
    tt.Equal(t, CallC(), "蒋佳威")
}

