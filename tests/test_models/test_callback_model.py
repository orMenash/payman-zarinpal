from zarinpal.models import CallbackParams


def test_callback_success():
    cb = CallbackParams(Authority="xyz", Status="OK")
    assert cb.is_success


def test_callback_failure():
    cb = CallbackParams(Authority="abc", Status="NOK")
    assert not cb.is_success
