from zarinpal.gateway import ZarinPal


def test_repr_contains_fields():
    gateway = ZarinPal("merchant-1", sandbox=True)
    rep = repr(gateway)
    assert "merchant-1" in rep
    assert "sandbox=True" in rep
