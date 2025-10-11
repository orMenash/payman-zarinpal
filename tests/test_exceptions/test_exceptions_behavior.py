from zarinpal.exception import ZarinPalGatewayException


def test_exception_str_contains_message():
    exc = ZarinPalGatewayException("something went wrong")
    assert "something went wrong" in str(exc)
